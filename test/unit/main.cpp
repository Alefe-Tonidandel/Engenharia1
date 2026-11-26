#include <iostream>
#include "unit_tests.h"
#include "unit_UsuarioImpl.h"
#include "unit_SessaoImpl.h"
#include "unit_ProdutoImpl.h"
#include "unit_LoteEstoqueImpl.h"
#include "unit_VendaImpl.h"
#include "unit_BancoImpl.h"
#include "unit_ServicoCadastrosImpl.h"
#include "unit_ServicoEstoqueImpl.h"
#include "unit_Dinheiro.h"
#include "unit_Data.h"
#include "unit_Relogio.h"
#include "unit_ItemEstoque.h"
#include "unit_Resultado.h"

int main() {
    std::cout << "Testes unitarios\n";
    run_unit_tests_globais();
    run_unit_tests_UsuarioImpl();
    run_unit_tests_SessaoImpl();
    run_unit_tests_ProdutoImpl();
    run_unit_tests_LoteEstoqueImpl();
    run_unit_tests_VendaImpl();
    run_unit_tests_BancoImpl();
    run_unit_tests_ServicoCadastrosImpl();
    run_unit_tests_ServicoEstoqueImpl();
    run_unit_tests_Dinheiro();
    run_unit_tests_Data();
    run_unit_tests_Relogio();
    run_unit_tests_ItemEstoque();
    run_unit_tests_Resultado();
    std::cout << "Todos os testes unitarios passaram.\n";
    return 0;
}