#include <cassert>
#include "unit_Dinheiro.h"
#include "../../src/dinheiro.h"

void unit_Dinheiro_construtor(void){
    Dinheiro zero;
    assert(zero.centavos() == 0);
}

void unit_Dinheiro_copyConstrutor(void) {
    Dinheiro preco = Dinheiro::reais(11.20);
    Dinheiro copia(preco);
    assert(copia.centavos() == 1120);

}

void unit_Dinheiro_operatorAtribuicao(void){
    Dinheiro preco = Dinheiro::reais(8.40);
    Dinheiro d;
    d = preco;
    assert(d.centavos() == 840);

}

void unit_Dinheiro_destrutor(void){
    Dinheiro* d = new Dinheiro(Dinheiro::reais(11.20));
    delete d; 
}

void unit_Dinheiro_reais(void){
    assert(Dinheiro::reais(11.20).centavos() == 1120);
    assert(Dinheiro::reais(4.49).centavos() == 449);

}

void unit_Dinheiro_centavos(void){
    Dinheiro custo = Dinheiro::reais(8.40);
    assert(custo.centavos() == 840);

}

void unit_Dinheiro_operatorMultiplicacao(void){
    Dinheiro preco = Dinheiro::reais(11.20);
    assert(preco * 2 == Dinheiro::reais(22.40));
    assert(preco * 40 == Dinheiro::reais(448.00));
    assert(Dinheiro::reais(0.10) * 3 == Dinheiro::reais(0.30));
}

void unit_Dinheiro_operatorMenor(void){
    Dinheiro custo = Dinheiro::reais(8.40);
    assert(Dinheiro::reais(7.00) < custo);
    assert(!(Dinheiro::reais(11.20) < custo));
    assert(!(custo < custo)); //igual n eh menor
}

void unit_Dinheiro_operatorIgual(void){
    assert(Dinheiro::reais(11.20) == Dinheiro::reais(11.20));
    assert(!(Dinheiro::reais(11.20) == Dinheiro::reais(12.00)));
}
void run_unit_tests_Dinheiro(void){
    unit_Dinheiro_construtor();
    unit_Dinheiro_copyConstrutor();
    unit_Dinheiro_operatorAtribuicao();
    unit_Dinheiro_destrutor();
    unit_Dinheiro_reais();
    unit_Dinheiro_centavos();
    unit_Dinheiro_operatorMultiplicacao();
    unit_Dinheiro_operatorMenor();
    unit_Dinheiro_operatorIgual();
}