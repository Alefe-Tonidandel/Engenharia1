#include <cassert>
#include <iostream>
#include "unit_tests.h"
#include "../../src/dinheiro.h"
#include "../../src/data.h"
#include "../../src/lote.h"
#include "../../src/produto.h"
#include "../../src/banco.h"
#include "../../src/usuario.h"
#include "../../src/tipos.h"

void testarDinheiro() {
    assert(Dinheiro::reais(11.20).centavos() == 1120);
    assert(Dinheiro::reais(11.20) * 2 == Dinheiro::reais(22.40));   // exato
    assert(Dinheiro::reais(0.10) * 3 == Dinheiro::reais(0.30));     // double daria erro
    assert(Dinheiro::reais(7.00) < Dinheiro::reais(8.40));
    assert(!(Dinheiro::reais(8.40) < Dinheiro::reais(8.40)));
    assert(Dinheiro().centavos() == 0);
    std::cout << "  testarDinheiro OK\n";
}

void testarData() {
    assert(Data(2026, 10, 30) < Data(2026, 11, 5));
    assert(Data(2025, 12, 31) < Data(2026, 1, 1));
    assert(!(Data(2026, 10, 30) < Data(2026, 10, 30)));
    assert(Data(2026, 10, 30) == Data(2026, 10, 30));
    Relogio::fixar(Data(2026, 10, 26));
    assert(Relogio::hoje() == Data(2026, 10, 26));
    std::cout << "  testarData OK\n";
}

void testarLote() {
    LoteEstoque l(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    assert(l.saldo() == 30 && l.quantidadeInicial() == 30);
    assert(!l.vencido(Data(2026, 10, 30)));    // vale ate o dia da validade
    assert(l.vencido(Data(2026, 10, 31)));
    l.baixar(5);
    assert(l.saldo() == 25 && l.quantidadeInicial() == 30);
    std::cout << "  testarLote OK\n";
}

void testarProduto() {
    Produto p("BP-1265", "Tomate italiano (kg)", "Hortifruti",
              Dinheiro::reais(8.40), 20);
    assert(!p.temPreco());                      // recem-cadastrado: sem preco
    p.setPreco(Dinheiro::reais(11.20));
    assert(p.temPreco() && p.preco() == Dinheiro::reais(11.20));
    assert(p.custo() == Dinheiro::reais(8.40) && p.estoqueMinimo() == 20);
    std::cout << "  testarProduto OK\n";
}

void testarResultado() {
    Resultado<int> ok = Resultado<int>::sucesso(7);
    assert(ok.ok() && ok.valor == 7);
    Resultado<int> ruim = Resultado<int>::falha(Erro::NaoEncontrado, "x");
    assert(!ruim.ok() && ruim.erro == Erro::NaoEncontrado && ruim.mensagem == "x");
    std::cout << "  testarResultado OK\n";
}

// Forma canonica: construtor de copia e atribuicao geram copias INDEPENDENTES
void testarFormaCanonica() {
    Produto a("BP-1", "Arroz", "Mercearia", Dinheiro::reais(22.0), 40);
    Produto b(a);                               // construtor de copia
    b.setPreco(Dinheiro::reais(26.90));
    assert(!a.temPreco() && b.temPreco());      // alterar b nao altera a

    Produto c;                                  // construtor padrao
    c = b;                                      // atribuicao
    assert(c.codigo() == "BP-1" && c.preco() == b.preco());
    c = c;                                      // auto-atribuicao segura
    assert(c.codigo() == "BP-1");

    Banco x;
    x.adicionarProduto(a);
    Banco y(x);                                 // copia do banco inteiro
    y.buscarProduto("BP-1")->setPreco(Dinheiro::reais(30.0));
    assert(!x.buscarProduto("BP-1")->temPreco());
    Banco z;
    z = y;
    assert(z.buscarProduto("BP-1")->temPreco());

    Sessao s1(Usuario(1, "Ana", Perfil::GestorRede, 0));
    Sessao s2(s1);
    assert(s2.usuario().nome() == "Ana" && s2.usuario().perfil() == Perfil::GestorRede);
    std::cout << "  testarFormaCanonica OK\n";
}
