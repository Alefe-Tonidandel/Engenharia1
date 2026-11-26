#include "servico_estoque_impl.h"
#include <algorithm>
#include <vector>

typedef Resultado<const LoteEstoque*> ResLote;
typedef Resultado<const Venda*>       ResVenda;

ServicoEstoqueImpl::ServicoEstoqueImpl() : sessao_(nullptr), banco_(nullptr) {}
ServicoEstoqueImpl::ServicoEstoqueImpl(const Sessao& sessao, Banco& banco)
    : sessao_(&sessao), banco_(&banco) {}
ServicoEstoqueImpl::ServicoEstoqueImpl(const ServicoEstoqueImpl& o)
    : ServicoEstoque(), sessao_(o.sessao_), banco_(o.banco_) {}
ServicoEstoqueImpl& ServicoEstoqueImpl::operator=(const ServicoEstoqueImpl& o) {
    if (this != &o) { sessao_ = o.sessao_; banco_ = o.banco_; }
    return *this;
}
ServicoEstoqueImpl::~ServicoEstoqueImpl() {}

static bool menorValidade(const LoteEstoque* a, const LoteEstoque* b) {
    return a->validade() < b->validade();
}

ResLote ServicoEstoqueImpl::registrarEntrada(const std::string& codigo,
                                         int quantidade, const Data& validade) {
    if (!sessao_ || !banco_)
        return ResLote::falha(Erro::AcessoNegado, "Sem sessao");
    const Usuario& eu = sessao_->usuario();
    if (eu.perfil() != Perfil::RepositorEstoque &&
        eu.perfil() != Perfil::GerenteUnidade)
        return ResLote::falha(Erro::AcessoNegado,
                              "Perfil sem permissao para registrar entrada");
    if (quantidade <= 0)
        return ResLote::falha(Erro::QuantidadeInvalida,
                              "Quantidade deve ser maior que zero");
    if (!banco_->buscarProduto(codigo))
        return ResLote::falha(Erro::NaoEncontrado, "Produto inexistente");
    Data hoje = Relogio::hoje();
    if (validade < hoje)
        return ResLote::falha(Erro::ValidadeVencida, "Validade ja passou");

    const LoteEstoque& l = banco_->adicionarLote(eu.idUnidade(), codigo, quantidade,
                                          hoje, validade);
    return ResLote::sucesso(&l);
}

ResVenda ServicoEstoqueImpl::registrarVenda(const std::string& codigo,
                                        int quantidade) {
    if (!sessao_ || !banco_)
        return ResVenda::falha(Erro::AcessoNegado, "Sem sessao");
    const Usuario& eu = sessao_->usuario();
    if (eu.perfil() != Perfil::OperadorCaixa &&
        eu.perfil() != Perfil::GerenteUnidade)
        return ResVenda::falha(Erro::AcessoNegado,
                               "Perfil sem permissao para registrar venda");
    if (quantidade <= 0)
        return ResVenda::falha(Erro::QuantidadeInvalida,
                               "Quantidade deve ser maior que zero");
    const Produto* p = banco_->buscarProduto(codigo);
    if (!p)
        return ResVenda::falha(Erro::NaoEncontrado, "Produto inexistente");
    if (!p->temPreco())
        return ResVenda::falha(Erro::ProdutoSemPreco, "Produto sem preco");

    Data hoje = Relogio::hoje();
    if (quantidade > banco_->saldoValido(eu.idUnidade(), codigo, hoje))
        return ResVenda::falha(Erro::EstoqueInsuficiente,
                               "Estoque valido insuficiente");

    // lotes validos da unidade, do que vence primeiro para o que vence depois
    std::vector<LoteEstoque*> candidatos;
    for (int i = 0; i < banco_->quantidadeLotes(); ++i) {
        LoteEstoque& l = banco_->lote(i);
        if (l.idUnidade() == eu.idUnidade() && l.codigoProduto() == codigo && l.saldo() > 0 && !l.vencido(hoje))
            candidatos.push_back(&l);
    }
    std::stable_sort(candidatos.begin(), candidatos.end(), menorValidade);

    int falta = quantidade;
    for (size_t i = 0; i < candidatos.size() && falta > 0; ++i) {
        int tira = std::min(falta, candidatos[i]->saldo());
        candidatos[i]->baixar(tira);
        falta -= tira;
    }

    const Venda& v = banco_->adicionarVenda(eu.idUnidade(), codigo, quantidade,
                                     p->preco() * quantidade, hoje, eu.id());
    return ResVenda::sucesso(&v);
}

Resultado<std::vector<ItemEstoque> >
ServicoEstoqueImpl::consultarEstoque(const FiltroEstoque& filtro) {
    typedef Resultado<std::vector<ItemEstoque> > ResItens;
    if (!sessao_ || !banco_)
        return ResItens::falha(Erro::AcessoNegado, "Sem sessao");

    const Usuario& eu = sessao_->usuario();
    Perfil perfil = eu.perfil();

    int idUnidade = 0;
    if (perfil == Perfil::RepositorEstoque || perfil == Perfil::GerenteUnidade) {
        if (filtro.idUnidade.has_value() && *filtro.idUnidade != eu.idUnidade())
            return ResItens::falha(Erro::AcessoNegado,
                                   "Consulta restrita a propria unidade");
        idUnidade = eu.idUnidade();
    } else if (perfil == Perfil::GestorRede || perfil == Perfil::Administrador) {
        if (!filtro.idUnidade.has_value())
            return ResItens::falha(Erro::UnidadeNaoInformada,
                                   "Informe a unidade a consultar");
        idUnidade = *filtro.idUnidade;
    } else {
        return ResItens::falha(Erro::AcessoNegado,
                               "Perfil sem permissao para consultar estoque");
    }

    Data hoje = Relogio::hoje();
    std::vector<ItemEstoque> itens;

    for (int i = 0; i < banco_->quantidadeProdutos(); ++i) {
        const Produto& p = banco_->produto(i);
        if (!filtro.categoria.empty() && p.categoria() != filtro.categoria)
            continue;

        int valida = 0, vencida = 0;
        bool temValidade = false;
        Data proxima;

        for (int j = 0; j < banco_->quantidadeLotes(); ++j) {
            const LoteEstoque& l =banco_-> lote(j);
            if (l.idUnidade() != idUnidade || l.codigoProduto() != p.codigo()
                || l.saldo() <= 0)
                continue;

            if (l.vencido(hoje)) {
                vencida += l.saldo();
            } else {
                valida += l.saldo();
                if (!temValidade || l.validade() < proxima) {
                    proxima = l.validade();
                    temValidade = true;
                }
            }
        }

        itens.push_back(ItemEstoque(p.codigo(), p.nome(), valida, vencida,
                                    p.estoqueMinimo(), temValidade, proxima));
    }

    return ResItens::sucesso(itens);
}
