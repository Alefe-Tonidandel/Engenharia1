#include <cassert>
#include <sstream>
#include "unit_tests.h"
#include "../../src/data.h"
#include "../../src/dinheiro.h"

void unit_operator_saida_Data(void){
    std::ostringstream s1;
    s1 << Data(2026, 10, 30);             // "imprime" a data dentro de s1
    assert(s1.str() == "30/10/2026");     // confere o texto que saiu
}

void unit_operator_saida_Dinheiro(void){
    std::ostringstream s1;
    s1 << Dinheiro::reais(22.40);
    assert(s1.str() == "R$ 22,40");
}

void run_unit_tests_globais(void){
    unit_operator_saida_Data();
    unit_operator_saida_Dinheiro();
}