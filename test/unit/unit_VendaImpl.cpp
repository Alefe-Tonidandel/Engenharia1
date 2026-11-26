#include <cassert>
#include "unit_VendaImpl.h"
#include "../../src/venda_impl.h"


void unit_VendaImpl_construtor(void){
    VendaImpl vazio;
    assert(vazio.quantidade() == 0);

    VendaImpl L1(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    assert(L1.id() == 1 && L1.idUnidade() == 1 && L1.codigoProduto() == "BP-1265" && L1.quantidade() == 2 && L1.valorTotal() == Dinheiro::reais(22.40) && L1.data() == Data(2026,10,28) && L1.idUsuario() == 31);

    VendaImpl L2(2, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 31), 31);
    assert(L2.id() == 2 && L2.idUnidade() == 1 && L2.codigoProduto() == "BP-1265" && L2.quantidade() == 2 && L2.valorTotal() == Dinheiro::reais(22.40) && L2.data() == Data(2026,10,31) && L2.idUsuario() == 31);

    VendaImpl L3(3, 1, "BP-1265", 40, Dinheiro::reais(448.0), Data(2026, 10, 31), 31);
    assert(L3.id() == 3 && L3.idUnidade() == 1 && L3.codigoProduto() == "BP-1265" && L3.quantidade() == 40 && L3.valorTotal() == Dinheiro::reais(448.0) && L3.data() == Data(2026,10,31) && L3.idUsuario() == 31);

    //ID, IDUNIDADE, COD PRODUTO, QTD, VALORTOTAL, DATA, IDUSUARIO
    
}

void unit_VendaImpl_copyConstrutor(void) {
    VendaImpl tomate(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    VendaImpl copia(tomate);
    assert(copia.id() == 1 && copia.idUnidade() == 1 && copia.codigoProduto() == "BP-1265" && copia.quantidade() == 2 && copia.valorTotal() == Dinheiro::reais(22.40) && copia.data() == Data(2026,10,28) && copia.idUsuario() == 31);

}

void unit_VendaImpl_operatorAtribuicao(void){
    VendaImpl tomate(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    VendaImpl v1;
    v1 = tomate;
    assert(v1.id() == 1 && v1.idUnidade() == 1 && v1.codigoProduto() == "BP-1265" && v1.quantidade() == 2 && v1.valorTotal() == Dinheiro::reais(22.40) && v1.data() == Data(2026,10,28) && v1.idUsuario() == 31);
    
}

void unit_VendaImpl_destrutor(void){
    VendaImpl* venda = new VendaImpl(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    delete venda;

}

void unit_VendaImpl_id(void){
    VendaImpl tomate(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    assert(tomate.id() == 1);

}

void unit_VendaImpl_idUnidade(void){
    VendaImpl tomate(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    assert(tomate.idUnidade() == 1);
}


void unit_VendaImpl_codigoProduto(void){
    VendaImpl tomate(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    assert(tomate.codigoProduto() == "BP-1265");
}

void unit_VendaImpl_quantidade(void){
    VendaImpl tomate(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    assert(tomate.quantidade() == 2);
}

void unit_VendaImpl_valorTotal(void){
    VendaImpl tomate(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    assert(tomate.valorTotal() == Dinheiro::reais(22.40));
}

void unit_VendaImpl_data(void){
    VendaImpl tomate(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    assert(tomate.data() == Data(2026,10,28));
}

void unit_VendaImpl_idUsuario(void){
    VendaImpl tomate(1, 1, "BP-1265", 2, Dinheiro::reais(22.40), Data(2026, 10, 28), 31);
    assert(tomate.idUsuario() == 31);
}

void run_unit_tests_VendaImpl(void){
    unit_VendaImpl_construtor();
    unit_VendaImpl_copyConstrutor();
    unit_VendaImpl_operatorAtribuicao();
    unit_VendaImpl_destrutor();
    unit_VendaImpl_id();
    unit_VendaImpl_idUnidade();
    unit_VendaImpl_codigoProduto();
    unit_VendaImpl_quantidade();
    unit_VendaImpl_valorTotal();
    unit_VendaImpl_data();
    unit_VendaImpl_idUsuario();
}
