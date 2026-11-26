#include <cassert>
#include "unit_BancoImpl.h"
#include "../../src/banco_impl.h"

// ---- dados da Sprint 2 usados em varios testes ----
static ProdutoImpl tomate() {
    ProdutoImpl p("BP-1265", "Tomate italiano (kg)", "Hortifruti", Dinheiro::reais(8.40), 20);
    p.setPreco(Dinheiro::reais(11.20));
    return p;
}
static ProdutoImpl feijao() {   // fica "sem preco"
    return ProdutoImpl("BP-0999", "Feijao preto 1 kg", "Mercearia", Dinheiro::reais(6.80), 30);
}


void unit_BancoImpl_construtor(void){
    BancoImpl banco;
    assert(banco.quantidadeProdutos() == 0 && banco.quantidadeLotes() == 0 && banco.quantidadeVendas() == 0);

}

void unit_BancoImpl_copyConstrutor(void){
    BancoImpl original;
    original.adicionarProduto(feijao());
    BancoImpl copia(original);
    assert(copia.quantidadeProdutos() == 1 && copia.buscarProduto("BP-0999") != nullptr);

    copia.buscarProduto("BP-0999")->setPreco(Dinheiro::reais(8.00));
    assert(!original.buscarProduto("BP-0999")->temPreco());
}

void unit_BancoImpl_operatorAtribuicao(void){
    BancoImpl original;
    original.adicionarProduto(tomate());
    original.adicionarLote(1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    BancoImpl b;
    b = original;
    assert(b.quantidadeProdutos() == 1 && b.quantidadeLotes() == 1);
}

void unit_BancoImpl_destrutor(void){
    BancoImpl* banco = new BancoImpl();
    banco->adicionarProduto(tomate());
    delete banco;   

}

void unit_BancoImpl_buscarProduto(void){
    BancoImpl banco;
    banco.adicionarProduto(tomate());
    assert(banco.buscarProduto("BP-1265") != nullptr && banco.buscarProduto("BP-1265")->nome() == "Tomate italiano (kg)" && banco.buscarProduto("BP-0000") == nullptr);   // nao existe no catalogo
 
}


void unit_BancoImpl_adicionarProduto(void){
    BancoImpl banco;
    banco.adicionarProduto(tomate());
    banco.adicionarProduto(feijao());
    const Produto* t = banco.buscarProduto("BP-1265");
    assert(t->custo() == Dinheiro::reais(8.40));
    assert(t->preco() == Dinheiro::reais(11.20));     // o preco tambem e guardado
    assert(!banco.buscarProduto("BP-0999")->temPreco());
}

void unit_BancoImpl_quantidadeProdutos(void){
    BancoImpl banco;
    banco.adicionarProduto(tomate());
    banco.adicionarProduto(feijao());
    assert(banco.quantidadeProdutos() == 2);
}

void unit_BancoImpl_produto(void){
    BancoImpl banco;
    banco.adicionarProduto(tomate());
    banco.adicionarProduto(feijao());
    assert(banco.produto(0).codigo() == "BP-1265");   // na ordem em que foram adicionados
    assert(banco.produto(1).codigo() == "BP-0999");
}

void unit_BancoImpl_adicionarLote(void){
    BancoImpl banco;
    const LoteEstoque& l1 = banco.adicionarLote(1, "BP-1265", 30,
                                                Data(2026, 10, 26), Data(2026, 10, 30));
    assert(l1.id() == 1);                             // o banco numera os lotes
    assert(l1.idUnidade() == 1 && l1.codigoProduto() == "BP-1265");
    assert(l1.saldo() == 30 && l1.validade() == Data(2026, 10, 30));

    const LoteEstoque& l2 = banco.adicionarLote(1, "BP-1265", 50,
                                                Data(2026, 10, 26), Data(2026, 11, 5));
    assert(l2.id() == 2);
}

void unit_BancoImpl_quantidadeLotes(void){
    BancoImpl banco;
    banco.adicionarLote(1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    banco.adicionarLote(1, "BP-1265", 50, Data(2026, 10, 26), Data(2026, 11, 5));
    banco.adicionarLote(1, "BP-0501", 100, Data(2026, 10, 26), Data(2027, 3, 1));
    banco.adicionarLote(1, "BP-0720", 40, Data(2026, 10, 26), Data(2026, 12, 15));
    assert(banco.quantidadeLotes() == 4);             // os 4 lotes da Tabela 4
}

void unit_BancoImpl_lote(void){
    BancoImpl banco;
    banco.adicionarLote(1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    banco.adicionarLote(1, "BP-1265", 50, Data(2026, 10, 26), Data(2026, 11, 5));
    assert(banco.lote(1).saldo() == 50);

    banco.lote(0).baixar(2);                          // a versao nao-const permite alterar
    assert(banco.lote(0).saldo() == 28);
}

void unit_BancoImpl_buscarLote(void){
    BancoImpl banco;
    banco.adicionarLote(1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    banco.adicionarLote(1, "BP-0720", 40, Data(2026, 10, 26), Data(2026, 12, 15));
    assert(banco.buscarLote(2) != nullptr);
    assert(banco.buscarLote(2)->codigoProduto() == "BP-0720");
    assert(banco.buscarLote(99) == nullptr);          // lote que nao existe
}

void unit_BancoImpl_saldoValido(void){
    BancoImpl banco;
    banco.adicionarLote(1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    banco.adicionarLote(1, "BP-1265", 50, Data(2026, 10, 26), Data(2026, 11, 5));
    assert(banco.saldoValido(1, "BP-1265", Data(2026, 10, 28)) == 80);   // os dois validos
    assert(banco.saldoValido(1, "BP-1265", Data(2026, 10, 31)) == 50);   // lote 1 vencido nao conta
    assert(banco.saldoValido(2, "BP-1265", Data(2026, 10, 28)) == 0);    // outra unidade
}

void unit_BancoImpl_adicionarVenda(void){
    BancoImpl banco;
    const Venda& v = banco.adicionarVenda(1, "BP-1265", 2, Dinheiro::reais(22.40),
                                          Data(2026, 10, 28), 31);
    assert(v.id() == 1);                              // o banco numera as vendas
    assert(v.quantidade() == 2 && v.valorTotal() == Dinheiro::reais(22.40));
    assert(v.idUsuario() == 31);                      // Pedro Alves
}

void unit_BancoImpl_quantidadeVendas(void){
    BancoImpl banco;
    banco.adicionarVenda(1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    banco.adicionarVenda(1, "BP-1265", 40, Dinheiro::reais(448.00), Data(2026, 10, 31), 31);
    assert(banco.quantidadeVendas() == 2);
}

void unit_BancoImpl_venda(void){
    BancoImpl banco;
    banco.adicionarVenda(1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    banco.adicionarVenda(1, "BP-1265", 40, Dinheiro::reais(448.00), Data(2026, 10, 31), 31);
    assert(banco.venda(1).id() == 2);
    assert(banco.venda(1).valorTotal() == Dinheiro::reais(448.00));
}

void run_unit_tests_BancoImpl(void){
    unit_BancoImpl_construtor();
    unit_BancoImpl_copyConstrutor();
    unit_BancoImpl_operatorAtribuicao();
    unit_BancoImpl_destrutor();
    unit_BancoImpl_buscarProduto();
    unit_BancoImpl_adicionarProduto();
    unit_BancoImpl_quantidadeProdutos();
    unit_BancoImpl_produto();
    unit_BancoImpl_adicionarLote();
    unit_BancoImpl_quantidadeLotes();
    unit_BancoImpl_lote();
    unit_BancoImpl_buscarLote();
    unit_BancoImpl_saldoValido();
    unit_BancoImpl_adicionarVenda();
    unit_BancoImpl_quantidadeVendas();
    unit_BancoImpl_venda();
}
