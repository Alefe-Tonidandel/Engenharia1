#include <cassert>
#include "unit_Data.h"
#include "../../src/data.h"

void unit_Data_construtor(void){
    Data padrao; 
    assert(padrao.ano() == 1970 && padrao.mes() == 1 && padrao.dia() == 1);

    Data entrada(2026, 10, 26);
    assert(entrada.ano() == 2026 && entrada.mes() == 10 && entrada.dia() == 26);
}

void unit_Data_copyConstrutor(void){
    Data validade(2026, 10, 30);
    Data copia(validade);
    assert(copia.ano() == 2026 && copia.mes() == 10 && copia.dia() == 30);
}

void unit_Data_operatorAtribuicao(void){
    Data validadeL2(2026, 11, 5);
    Data d;
    d = validadeL2;
    assert(d.ano() == 2026 && d.mes() == 11 && d.dia() == 5);
}

void unit_Data_destrutor(void){
    Data* d = new Data(2026, 10, 31);
    delete d;                                         // nao pode dar erro
}

void unit_Data_ano(void){
    Data venda(2026, 10, 31);
    assert(venda.ano() == 2026);
}

void unit_Data_mes(void){
    Data venda(2026, 10, 31);
    assert(venda.mes() == 10);
}

void unit_Data_dia(void){
    Data venda(2026, 10, 31);
    assert(venda.dia() == 31);
}

void unit_Data_operatorMenor(void){
    assert(Data(2026, 10, 30) < Data(2026, 11, 5));    // lote 1 vence antes do lote 2
    assert(Data(2026, 10, 30) < Data(2026, 10, 31));   // validade do lote 1 < dia da venda
    assert(Data(2026, 12, 15) < Data(2027, 3, 1));     // leite vence antes do arroz (ano diferente)
    assert(!(Data(2026, 11, 5) < Data(2026, 10, 30)));
    assert(!(Data(2026, 10, 30) < Data(2026, 10, 30)));   // igual nao e menor
}

void unit_Data_operatorIgual(void){
    assert(Data(2026, 10, 30) == Data(2026, 10, 30));
    assert(!(Data(2026, 10, 30) == Data(2026, 10, 31)));
}

void run_unit_tests_Data(void){
    unit_Data_construtor();
    unit_Data_copyConstrutor();
    unit_Data_operatorAtribuicao();
    unit_Data_destrutor();
    unit_Data_ano();
    unit_Data_mes();
    unit_Data_dia();
    unit_Data_operatorMenor();
    unit_Data_operatorIgual();
}
