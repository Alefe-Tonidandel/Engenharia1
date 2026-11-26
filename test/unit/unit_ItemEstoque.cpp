#include <cassert>
#include "unit_ItemEstoque.h"
#include "../../src/item_estoque.h"

void unit_ItemEstoque_construtor(void){
    ItemEstoque vazio;
    assert(vazio.codigoProduto().empty() && vazio.quantidade() == 0);
    assert(!vazio.temValidade());

    ItemEstoque tomate("BP-1265", "Tomate italiano (kg)", 80, 0, 20, true, Data(2026, 10, 30));
    assert(tomate.codigoProduto() == "BP-1265" && tomate.nome() == "Tomate italiano (kg)");
    assert(tomate.quantidade() == 80 && tomate.quantidadeVencida() == 0);
    assert(tomate.estoqueMinimo() == 20 && tomate.temValidade());
    assert(tomate.validadeMaisProxima() == Data(2026, 10, 30));
}

void unit_ItemEstoque_copyConstrutor(void){
    ItemEstoque leite("BP-0720", "Leite integral 1 L", 40, 0, 60, true, Data(2026, 12, 15));
    ItemEstoque copia(leite);
    assert(copia.codigoProduto() == "BP-0720" && copia.quantidade() == 40);
    assert(copia.estoqueMinimo() == 60 && copia.validadeMaisProxima() == Data(2026, 12, 15));
}

void unit_ItemEstoque_operatorAtribuicao(void){
    ItemEstoque tomate("BP-1265", "Tomate italiano (kg)", 50, 30, 20, true, Data(2026, 11, 5));
    ItemEstoque i;
    i = tomate;
    assert(i.codigoProduto() == "BP-1265" && i.quantidade() == 50);
    assert(i.quantidadeVencida() == 30);
    i = i;                                            // auto-atribuicao nao estraga
    assert(i.quantidade() == 50);
}

void unit_ItemEstoque_destrutor(void){
    ItemEstoque* i = new ItemEstoque("BP-1265", "Tomate italiano (kg)", 80, 0, 20,
                                     true, Data(2026, 10, 30));
    delete i;                                         // nao pode dar erro
}

void unit_ItemEstoque_codigoProduto(void){
    ItemEstoque leite("BP-0720", "Leite integral 1 L", 40, 0, 60, true, Data(2026, 12, 15));
    assert(leite.codigoProduto() == "BP-0720");
}

void unit_ItemEstoque_nome(void){
    ItemEstoque leite("BP-0720", "Leite integral 1 L", 40, 0, 60, true, Data(2026, 12, 15));
    assert(leite.nome() == "Leite integral 1 L");
}

void unit_ItemEstoque_quantidade(void){
    ItemEstoque tomate("BP-1265", "Tomate italiano (kg)", 80, 0, 20, true, Data(2026, 10, 30));
    assert(tomate.quantidade() == 80);                // 30 do lote 1 + 50 do lote 2
}

void unit_ItemEstoque_quantidadeVencida(void){
    ItemEstoque tomate("BP-1265", "Tomate italiano (kg)", 50, 30, 20, true, Data(2026, 11, 5));
    assert(tomate.quantidadeVencida() == 30);         // em 31/10 o lote 1 ja venceu
}

void unit_ItemEstoque_estoqueMinimo(void){
    ItemEstoque leite("BP-0720", "Leite integral 1 L", 40, 0, 60, true, Data(2026, 12, 15));
    assert(leite.estoqueMinimo() == 60);
}

void unit_ItemEstoque_temValidade(void){
    ItemEstoque tomate("BP-1265", "Tomate italiano (kg)", 80, 0, 20, true, Data(2026, 10, 30));
    assert(tomate.temValidade());

    ItemEstoque feijao("BP-0999", "Feijao preto 1 kg", 0, 0, 30, false, Data());
    assert(!feijao.temValidade());                    // sem nenhum lote valido
}

void unit_ItemEstoque_validadeMaisProxima(void){
    ItemEstoque tomate("BP-1265", "Tomate italiano (kg)", 80, 0, 20, true, Data(2026, 10, 30));
    assert(tomate.validadeMaisProxima() == Data(2026, 10, 30));   // o lote 1 vence primeiro
}

void unit_ItemEstoque_abaixoDoMinimo(void){
    ItemEstoque leite("BP-0720", "Leite integral 1 L", 40, 0, 60, true, Data(2026, 12, 15));
    assert(leite.abaixoDoMinimo());                   // 40 < 60

    ItemEstoque tomate("BP-1265", "Tomate italiano (kg)", 80, 0, 20, true, Data(2026, 10, 30));
    assert(!tomate.abaixoDoMinimo());                 // 80 >= 20
}

void run_unit_tests_ItemEstoque(void){
    unit_ItemEstoque_construtor();
    unit_ItemEstoque_copyConstrutor();
    unit_ItemEstoque_operatorAtribuicao();
    unit_ItemEstoque_destrutor();
    unit_ItemEstoque_codigoProduto();
    unit_ItemEstoque_nome();
    unit_ItemEstoque_quantidade();
    unit_ItemEstoque_quantidadeVencida();
    unit_ItemEstoque_estoqueMinimo();
    unit_ItemEstoque_temValidade();
    unit_ItemEstoque_validadeMaisProxima();
    unit_ItemEstoque_abaixoDoMinimo();
}
