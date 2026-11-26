#include <cassert>
#include "unit_ProdutoImpl.h"
#include "../../src/produto_impl.h"

void unit_ProdutoImpl_construtor(void){
    ProdutoImpl vazio;
    assert(vazio.codigo().empty());
    assert(!vazio.temPreco());

    ProdutoImpl tomate("BP-1265", "tomate", "Hortifruti", Dinheiro::reais(8.40), 20);
    assert(tomate.codigo() == "BP-1265" && tomate.nome() == "tomate" && tomate.categoria() == "Hortifruti" && 
    tomate.custo() == Dinheiro::reais(8.40) && tomate.estoqueMinimo() == 20);
    assert(!tomate.temPreco());      
}

void unit_ProdutoImpl_copyConstrutor(void) {
    ProdutoImpl tomate("BP-1265", "tomate", "Hortifruti", Dinheiro::reais(8.40), 20);
    ProdutoImpl copia(tomate);
    assert(copia.codigo() == "BP-1265" && copia.nome() == "tomate" && copia.categoria() == "Hortifruti" && 
    copia.custo() == Dinheiro::reais(8.40) && copia.estoqueMinimo() == 20);
    assert(!copia.temPreco()); 

    //copia eh independente 
    copia.setPreco(Dinheiro::reais(11.20));
    assert(!tomate.temPreco());
    
}

void unit_ProdutoImpl_operatorAtribuicao(void){
    ProdutoImpl tomate("BP-1265", "tomate", "Hortifruti", Dinheiro::reais(8.40), 20);
    ProdutoImpl p1;
    p1 = tomate;
    assert(p1.codigo() == "BP-1265" && p1.nome() == "tomate" && p1.categoria() == "Hortifruti" && 
    p1.custo() == Dinheiro::reais(8.40) && p1.estoqueMinimo() == 20);
    assert(!p1.temPreco()); 
}

void unit_ProdutoImpl_destrutor(void){
    ProdutoImpl* p = new ProdutoImpl("BP-1265", "tomate", "Hortifruti", Dinheiro::reais(8.40), 20);
    delete p;
}

void unit_ProdutoImpl_codigo(void){
    ProdutoImpl feijao("BP-0999", "Feijao", "Mercearia", Dinheiro::reais(6.80), 30);
    assert(feijao.codigo() == "BP-0999");
}

void unit_ProdutoImpl_nome(void){
    ProdutoImpl feijao("BP-0999", "Feijao", "Mercearia", Dinheiro::reais(6.80), 30);
    assert(feijao.nome() == "Feijao");
}


void unit_ProdutoImpl_categoria(void){
    ProdutoImpl feijao("BP-0999", "Feijao", "Mercearia", Dinheiro::reais(6.80), 30);
    assert(feijao.categoria() == "Mercearia");
}

void unit_ProdutoImpl_custo(void){
    ProdutoImpl feijao("BP-0999", "Feijao", "Mercearia", Dinheiro::reais(6.80), 30);
    assert(feijao.custo() == Dinheiro::reais(6.80));
}

void unit_ProdutoImpl_preco(void){
    ProdutoImpl leite("BP-0720", "Leite integral 1L", "Laticinios", Dinheiro::reais(3.60), 60);
    assert(leite.preco() == Dinheiro());
    leite.setPreco(Dinheiro::reais(4.49));
    assert(leite.preco() == Dinheiro::reais(4.49));
}

void unit_ProdutoImpl_estoqueMinimo(void){
    ProdutoImpl feijao("BP-0999", "Feijao", "Mercearia", Dinheiro::reais(6.80), 30);
    assert(feijao.estoqueMinimo() == 30);
}

void unit_ProdutoImpl_temPreco(void){
    ProdutoImpl feijao("BP-0999", "Feijao", "Mercearia", Dinheiro::reais(6.80), 30);
    assert(!feijao.temPreco());

    ProdutoImpl arroz("BP-0501", "Arroz", "Mercearia", Dinheiro::reais(22.00), 40);
    arroz.setPreco(Dinheiro::reais(26.90));
    assert(arroz.temPreco());

}
void unit_ProdutoImpl_setPreco(void){
    ProdutoImpl tomate("BP-1265", "tomate", "Hortifruti", Dinheiro::reais(8.40), 20);
    tomate.setPreco(Dinheiro::reais(11.20));
    assert(tomate.preco() == Dinheiro::reais(11.20));
    tomate.setPreco(Dinheiro::reais(12.00));
    assert(tomate.preco() == Dinheiro::reais(12.00));
}


void run_unit_tests_ProdutoImpl(void) {
    unit_ProdutoImpl_construtor();
    unit_ProdutoImpl_copyConstrutor();
    unit_ProdutoImpl_operatorAtribuicao();
    unit_ProdutoImpl_destrutor();
    unit_ProdutoImpl_codigo();
    unit_ProdutoImpl_nome();
    unit_ProdutoImpl_categoria();
    unit_ProdutoImpl_custo();
    unit_ProdutoImpl_preco();
    unit_ProdutoImpl_estoqueMinimo();
    unit_ProdutoImpl_temPreco();
    unit_ProdutoImpl_setPreco();
}