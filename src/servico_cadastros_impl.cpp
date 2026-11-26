#include "servico_cadastros_impl.h"
#include "produto_impl.h"

typedef Resultado<const Produto*> ResProduto;

ServicoCadastrosImpl::ServicoCadastrosImpl() : sessao_(nullptr), banco_(nullptr) {}
ServicoCadastrosImpl::ServicoCadastrosImpl(const Sessao& sessao, Banco& banco)
    : sessao_(&sessao), banco_(&banco) {}
ServicoCadastrosImpl::ServicoCadastrosImpl(const ServicoCadastrosImpl& o)
    : ServicoCadastros(), sessao_(o.sessao_), banco_(o.banco_) {}
ServicoCadastrosImpl& ServicoCadastrosImpl::operator=(const ServicoCadastrosImpl& o) {
    if (this != &o) { sessao_ = o.sessao_; banco_ = o.banco_; }
    return *this;
}
ServicoCadastrosImpl::~ServicoCadastrosImpl() {}

bool ServicoCadastrosImpl::podeGerirCatalogo() const {
    if (!sessao_ || !banco_) return false;
    Perfil p = sessao_->usuario().perfil();
    return p == Perfil::GestorRede || p == Perfil::Administrador;
}

ResProduto ServicoCadastrosImpl::cadastrarProduto(const DadosProduto& d) {
    if (!podeGerirCatalogo())
        return ResProduto::falha(Erro::AcessoNegado,
                                 "Perfil sem permissao para cadastrar produto");
    if (d.codigo.empty() || d.nome.empty() || d.categoria.empty())
        return ResProduto::falha(Erro::CampoVazio,
                                 "Codigo, nome e categoria sao obrigatorios");
    if (d.custo.centavos() < 0)
        return ResProduto::falha(Erro::CustoInvalido, "Custo negativo");
    if (d.estoqueMinimo < 0)
        return ResProduto::falha(Erro::QuantidadeInvalida,
                                 "Estoque minimo negativo");
    if (banco_->buscarProduto(d.codigo))
        return ResProduto::falha(Erro::Duplicado, "Codigo ja cadastrado");

    ProdutoImpl p(d.codigo, d.nome, d.categoria, d.custo, d.estoqueMinimo);
    banco_->adicionarProduto(p);          // fica sem preco ate definirPrecoPadrao
    return ResProduto::sucesso(banco_->buscarProduto(d.codigo));
}

ResProduto ServicoCadastrosImpl::definirPrecoPadrao(const std::string& codigo,
                                                const Dinheiro& preco) {
    if (!podeGerirCatalogo())
        return ResProduto::falha(Erro::AcessoNegado,
                                 "Perfil sem permissao para definir preco");
    Produto* p = banco_->buscarProduto(codigo);
    if (!p)
        return ResProduto::falha(Erro::NaoEncontrado, "Produto inexistente");
    if (preco.centavos() <= 0 || preco < p->custo())
        return ResProduto::falha(Erro::PrecoAbaixoDoCusto,
                                 "Preco deve ser maior que zero e nao menor que o custo");

    p->setPreco(preco);                   // vale para todas as unidades
    return ResProduto::sucesso(p);
}
