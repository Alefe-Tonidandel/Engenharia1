#ifndef MAIN_UNIT_TESTS
#define MAIN_UNIT_TESTS
#include <iostream>
#include "unit_tests.h"

int main() {
    std::cout << "Testes unitarios\n";
    testarDinheiro();
    testarData();
    testarLote();
    testarProduto();
    testarResultado();
    testarFormaCanonica();
    std::cout << "Todos os testes unitarios passaram.\n";
    return 0;
}
#endif
