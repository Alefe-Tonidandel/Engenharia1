#include "servico_estoque.h"
#include <algorithm>
#include <vector>

typedef Resultado<LoteEstoque> ResLote;
typedef Resultado<Venda>       ResVenda;

ServicoEstoque::ServicoEstoque() : sessao_(nullptr), banco_(nullptr) {}
ServicoEstoque::ServicoEstoque(const Sessao& sessao, Banco& banco)
    : sessao_(&sessao), banco_(&banco) {}
ServicoEstoque::ServicoEstoque(const ServicoEstoque& o)
    : sessao_(o.sessao_), banco_(o.banco_) {}
ServicoEstoque& ServicoEstoque::operator=(const ServicoEstoque& o) {
    if (this != &o) { sessao_ = o.sessao_; banco_ = o.banco_; }
    return *this;
}
ServicoEstoque::~ServicoEstoque() {}

static bool menorValidade(const LoteEstoque* a, const LoteEstoque* b) {
    return a->validade() < b->validade();
}

ResLote ServicoEstoque::registrarEntrada(const std::string& codigo,
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

    LoteEstoque l = banco_->adicionarLote(eu.idUnidade(), codigo, quantidade,
                                          hoje, validade);
    return ResLote::sucesso(l);
}

ResVenda ServicoEstoque::registrarVenda(const std::string& codigo,
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
    std::vector<LoteEstoque>& todos = banco_->lotes();
    for (size_t i = 0; i < todos.size(); ++i) {
        LoteEstoque& l = todos[i];
        if (l.idUnidade() == eu.idUnidade() && l.codigoProduto() == codigo &&
            l.saldo() > 0 && !l.vencido(hoje))
            candidatos.push_back(&l);
    }
    std::stable_sort(candidatos.begin(), candidatos.end(), menorValidade);

    int falta = quantidade;
    for (size_t i = 0; i < candidatos.size() && falta > 0; ++i) {
        int tira = std::min(falta, candidatos[i]->saldo());
        candidatos[i]->baixar(tira);
        falta -= tira;
    }

    Venda v = banco_->adicionarVenda(eu.idUnidade(), codigo, quantidade,
                                     p->preco() * quantidade, hoje, eu.id());
    return ResVenda::sucesso(v);
}
