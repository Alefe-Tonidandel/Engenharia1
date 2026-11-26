#include <cassert>
#include "unit_Relogio.h"
#include "../../src/data.h"

void unit_Relogio_hoje(void){
    Relogio::fixar(Data(2026, 10, 26));
    assert(Relogio::hoje() == Data(2026, 10, 26));
    assert(Relogio::hoje() == Relogio::hoje());       // chamar de novo da a mesma data
}

void unit_Relogio_fixar(void){
    Relogio::fixar(Data(2026, 10, 26));               // dia das entradas
    assert(Relogio::hoje() == Data(2026, 10, 26));
    Relogio::fixar(Data(2026, 10, 31));               // dia da venda (lote 1 ja venceu)
    assert(Relogio::hoje() == Data(2026, 10, 31));
}

void run_unit_tests_Relogio(void){
    unit_Relogio_hoje();
    unit_Relogio_fixar();
}