#ifndef MAIN_FUNCIONAL_TESTS
#define MAIN_FUNCIONAL_TESTS
#include <iostream>
#include "funcional_tests.h"
#include "../../src/banco.h"
#include "../../src/servico_cadastros.h"
#include "../../src/servico_estoque.h"

int main() {
    std::cout << "Testes funcionais\n";
    cadastroFuncionalTest();
    entradaFuncionalTest();
    vendaFuncionalTest();
    std::cout << "Todos os testes funcionais passaram.\n";
    return 0;
}
#endif
