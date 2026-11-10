#include "servico_cadastros.h"

typedef Resultado<Produto> ResProduto;

ServicoCadastros::ServicoCadastros() : sessao_(nullptr), banco_(nullptr) {}
ServicoCadastros::ServicoCadastros(const Sessao& sessao, Banco& banco)
    : sessao_(&sessao), banco_(&banco) {}
ServicoCadastros::ServicoCadastros(const ServicoCadastros& o)
    : sessao_(o.sessao_), banco_(o.banco_) {}
ServicoCadastros& ServicoCadastros::operator=(const ServicoCadastros& o) {
    if (this != &o) { sessao_ = o.sessao_; banco_ = o.banco_; }
    return *this;
}
ServicoCadastros::~ServicoCadastros() {}

bool ServicoCadastros::podeGerirCatalogo() const {
    if (!sessao_ || !banco_) return false;
    Perfil p = sessao_->usuario().perfil();
    return p == Perfil::GestorRede || p == Perfil::Administrador;
}

ResProduto ServicoCadastros::cadastrarProduto(const DadosProduto& d) {
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

    Produto p(d.codigo, d.nome, d.categoria, d.custo, d.estoqueMinimo);
    banco_->adicionarProduto(p);          // fica sem preco ate definirPrecoPadrao
    return ResProduto::sucesso(p);
}

ResProduto ServicoCadastros::definirPrecoPadrao(const std::string& codigo,
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
    return ResProduto::sucesso(*p);
}
