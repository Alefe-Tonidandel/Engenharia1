/**
 * @file unit_ServicoCadastrosImpl.cpp
 * @brief Testes unitarios da classe ServicoCadastrosImpl
 *
 * Usa os cenarios 4.1 (cadastrar produto padrao) e 4.2 (definir preco padrao)
 * da Sprint 2. O Gestor da Rede e Rafael Lima; o Operador e Pedro Alves.
 */
#include <cassert>
#include "unit_ServicoCadastrosImpl.h"
#include "../../src/servico_cadastros_impl.h"
#include "../../src/banco_impl.h"
#include "../../src/sessao_impl.h"
#include "../../src/usuario_impl.h"

static DadosProduto dadosTomate() {
    DadosProduto d = {"BP-1265", "Tomate italiano (kg)", "Hortifruti", Dinheiro::reais(8.40), 20};
    return d;
}

void unit_ServicoCadastrosImpl_construtor(void){
    BancoImpl banco;
    ServicoCadastrosImpl semSessao;                   // construtor padrao: recusa tudo
    assert(semSessao.cadastrarProduto(dadosTomate()).erro == Erro::AcessoNegado);

    SessaoImpl gestor(UsuarioImpl(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoCadastrosImpl cadastros(gestor, banco);    // ligado a sessao e ao banco
    assert(cadastros.cadastrarProduto(dadosTomate()).ok());
    assert(banco.quantidadeProdutos() == 1);          // gravou no banco recebido
}

void unit_ServicoCadastrosImpl_copyConstrutor(void){
    BancoImpl banco;
    SessaoImpl gestor(UsuarioImpl(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoCadastrosImpl original(gestor, banco);
    ServicoCadastrosImpl copia(original);             // usa a mesma sessao e o mesmo banco
    assert(copia.cadastrarProduto(dadosTomate()).ok());
    assert(banco.quantidadeProdutos() == 1);
}

void unit_ServicoCadastrosImpl_operatorAtribuicao(void){
    BancoImpl banco;
    SessaoImpl gestor(UsuarioImpl(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoCadastrosImpl original(gestor, banco);
    ServicoCadastrosImpl s;
    s = original;
    assert(s.cadastrarProduto(dadosTomate()).ok());
    assert(banco.quantidadeProdutos() == 1);
}

void unit_ServicoCadastrosImpl_destrutor(void){
    BancoImpl banco;
    SessaoImpl gestor(UsuarioImpl(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoCadastrosImpl* s = new ServicoCadastrosImpl(gestor, banco);
    s->cadastrarProduto(dadosTomate());
    delete s;                                         // nao apaga a sessao nem o banco
    assert(banco.quantidadeProdutos() == 1);
}

void unit_ServicoCadastrosImpl_cadastrarProduto(void){
    BancoImpl banco;
    SessaoImpl gestor(UsuarioImpl(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoCadastrosImpl cadastros(gestor, banco);

    // ok: produto criado sem preco
    Resultado<const Produto*> r = cadastros.cadastrarProduto(dadosTomate());
    assert(r.ok());
    assert(r.valor->codigo() == "BP-1265" && !r.valor->temPreco());

    // codigo repetido
    assert(cadastros.cadastrarProduto(dadosTomate()).erro == Erro::Duplicado);

    // nome vazio
    DadosProduto semNome = {"BP-0999", "", "Mercearia", Dinheiro::reais(6.80), 30};
    assert(cadastros.cadastrarProduto(semNome).erro == Erro::CampoVazio);

    // custo -1,00
    DadosProduto custoNeg = {"BP-0999", "Feijao preto 1 kg", "Mercearia", Dinheiro::reais(-1.00), 30};
    assert(cadastros.cadastrarProduto(custoNeg).erro == Erro::CustoInvalido);

    // estoque minimo -5
    DadosProduto minimoNeg = {"BP-0999", "Feijao preto 1 kg", "Mercearia", Dinheiro::reais(6.80), -5};
    assert(cadastros.cadastrarProduto(minimoNeg).erro == Erro::QuantidadeInvalida);

    // Operador de Caixa tenta cadastrar
    SessaoImpl op(UsuarioImpl(31, "Pedro Alves", Perfil::OperadorCaixa, 1));
    ServicoCadastrosImpl caixa(op, banco);
    DadosProduto feijao = {"BP-0999", "Feijao preto 1 kg", "Mercearia", Dinheiro::reais(6.80), 30};
    assert(caixa.cadastrarProduto(feijao).erro == Erro::AcessoNegado);

    assert(banco.quantidadeProdutos() == 1);          // so o tomate foi gravado
}

void unit_ServicoCadastrosImpl_definirPrecoPadrao(void){
    BancoImpl banco;
    SessaoImpl gestor(UsuarioImpl(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoCadastrosImpl cadastros(gestor, banco);
    cadastros.cadastrarProduto(dadosTomate());

    // preco novo 11,20
    Resultado<const Produto*> r = cadastros.definirPrecoPadrao("BP-1265", Dinheiro::reais(11.20));
    assert(r.ok() && r.valor->preco() == Dinheiro::reais(11.20));

    // atualizar para 12,00
    assert(cadastros.definirPrecoPadrao("BP-1265", Dinheiro::reais(12.00)).ok());
    assert(banco.buscarProduto("BP-1265")->preco() == Dinheiro::reais(12.00));

    // 7,00 abaixo do custo 8,40: o preco anterior e mantido
    assert(cadastros.definirPrecoPadrao("BP-1265", Dinheiro::reais(7.00)).erro
           == Erro::PrecoAbaixoDoCusto);
    assert(banco.buscarProduto("BP-1265")->preco() == Dinheiro::reais(12.00));

    // preco 0,00
    assert(cadastros.definirPrecoPadrao("BP-1265", Dinheiro::reais(0.00)).erro
           == Erro::PrecoAbaixoDoCusto);

    // produto que nao existe
    assert(cadastros.definirPrecoPadrao("BP-0000", Dinheiro::reais(5.00)).erro
           == Erro::NaoEncontrado);
}

void run_unit_tests_ServicoCadastrosImpl(void){
    unit_ServicoCadastrosImpl_construtor();
    unit_ServicoCadastrosImpl_copyConstrutor();
    unit_ServicoCadastrosImpl_operatorAtribuicao();
    unit_ServicoCadastrosImpl_destrutor();
    unit_ServicoCadastrosImpl_cadastrarProduto();
    unit_ServicoCadastrosImpl_definirPrecoPadrao();
}
