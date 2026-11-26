/**
 * @file unit_LoteEstoqeImpl.cpp
 * @brief Testes unitarios da classe LoteEstoqueImpl
 * 
 */
#include <cassert>
#include "unit_LoteEstoqueImpl.h"
#include "../../src/lote_impl.h"

// usamos lotes da unidade 1 do cenario da sprint2 tab4 - todos deram entrada em 26/10/2026
void unit_LoteEstoqueImpl_construtor(void) {
    LoteEstoqueImpl vazio;                            // construtor padrao
    assert(vazio.id() == 0 && vazio.saldo() == 0 && vazio.codigoProduto().empty());

    LoteEstoqueImpl l1(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    assert(l1.id() == 1 && l1.saldo() == 30);                         // saldo comeca cheio
}

void unit_LoteEstoqueImpl_copyConstrutor(void) {
    LoteEstoqueImpl l1(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    LoteEstoqueImpl copia(l1);
    assert(copia.id() == 1 && copia.codigoProduto() == "BP-1265" && copia.saldo() == 30);
    copia.baixar(2);
    assert(l1.saldo() == 30 && copia.saldo() == 28);
}

void unit_LoteEstoqueImpl_operatorAtribuicao(void) {
    LoteEstoqueImpl l2(2, 1, "BP-1265", 50, Data(2026, 10, 26), Data(2026, 11, 5));
    LoteEstoqueImpl l;
    l = l2;
    assert(l.id() == 2 && l.validade() == Data(2026, 11, 5));
}

void unit_LoteEstoqueImpl_destructor(void) {
    LoteEstoqueImpl* l = new LoteEstoqueImpl(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    delete l;                                         // nao pode dar erro
}

void unit_LoteEstoqueImpl_id(void) {
    LoteEstoqueImpl l2(2, 1, "BP-1265", 50, Data(2026, 10, 26), Data(2026, 11, 5));
    assert(l2.id() == 2);
}

void unit_LoteEstoqueImpl_idUnidade(void) {
    LoteEstoqueImpl l1(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    assert(l1.idUnidade() == 1);
}

void unit_LoteEstoqueImpl_codigoProduto(void) {
    LoteEstoqueImpl l1(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    assert(l1.codigoProduto() == "BP-1265");
}

void unit_LoteEstoqueImpl_quantidadeInicial(void) {
    LoteEstoqueImpl l1(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    l1.baixar(2);
    assert(l1.quantidadeInicial() == 30);             // nao muda com a venda
}

void unit_LoteEstoqueImpl_saldo(void) {
    LoteEstoqueImpl l2(2, 1, "BP-1265", 50, Data(2026, 10, 26), Data(2026, 11, 5));
    assert(l2.saldo() == 50);
}

void unit_LoteEstoqueImpl_dataEntrada(void) {
    LoteEstoqueImpl l1(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    assert(l1.dataEntrada() == Data(2026, 10, 26));
}

void unit_LoteEstoqueImpl_validade(void) {
    LoteEstoqueImpl l1(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    assert(l1.validade() == Data(2026, 10, 30));
}

void unit_LoteEstoqueImpl_vencido(void) {
    LoteEstoqueImpl l1(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    assert(!l1.vencido(Data(2026, 10, 28)));          // 28/10: valido
    assert(!l1.vencido(Data(2026, 10, 30)));          // vale ate o dia da validade
    assert(l1.vencido(Data(2026, 10, 31)));           // 31/10: vencido
}

void unit_LoteEstoqueImpl_baixar(void) {
    LoteEstoqueImpl l1(1, 1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));
    l1.baixar(2);                                     // venda de 2 em 28/10
    assert(l1.saldo() == 28);

    LoteEstoqueImpl l2(2, 1, "BP-1265", 48, Data(2026, 10, 26), Data(2026, 11, 5));
    l2.baixar(40);                                    // venda de 40 em 31/10
    assert(l2.saldo() == 8);
}

void run_unit_tests_LoteEstoqueImpl(void) {
    unit_LoteEstoqueImpl_construtor();
    unit_LoteEstoqueImpl_copyConstrutor();
    unit_LoteEstoqueImpl_operatorAtribuicao();
    unit_LoteEstoqueImpl_destructor();
    unit_LoteEstoqueImpl_id();
    unit_LoteEstoqueImpl_idUnidade();
    unit_LoteEstoqueImpl_codigoProduto();
    unit_LoteEstoqueImpl_quantidadeInicial();
    unit_LoteEstoqueImpl_saldo();
    unit_LoteEstoqueImpl_dataEntrada();
    unit_LoteEstoqueImpl_validade();
    unit_LoteEstoqueImpl_vencido();
    unit_LoteEstoqueImpl_baixar();
}