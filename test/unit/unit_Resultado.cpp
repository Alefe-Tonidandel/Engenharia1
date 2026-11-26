/**
 * @file unit_Resultado.cpp
 * @brief Testes unitarios do template Resultado
 *
 * Resultado<T> e um template; os testes usam T = int e T = Dinheiro.
 * Os erros sao os dos cenarios da Sprint 2.
 */
#include <cassert>
#include "unit_Resultado.h"
#include "../../src/tipos.h"
#include "../../src/dinheiro.h"

void unit_Resultado_construtor(void){
    Resultado<int> r;                                 // comeca sem erro
    assert(r.valor == 0);
    assert(r.erro == Erro::Nenhum);
    assert(r.mensagem.empty());
}

void unit_Resultado_ok(void){
    Resultado<int> certo;
    assert(certo.ok());

    Resultado<int> errado;
    errado.erro = Erro::AcessoNegado;
    assert(!errado.ok());
}

void unit_Resultado_sucesso(void){
    Resultado<Dinheiro> r = Resultado<Dinheiro>::sucesso(Dinheiro::reais(22.40));
    assert(r.ok());
    assert(r.valor == Dinheiro::reais(22.40));        // total da venda de 2 tomates
    assert(r.erro == Erro::Nenhum);
}

void unit_Resultado_falha(void){
    Resultado<Dinheiro> r = Resultado<Dinheiro>::falha(Erro::EstoqueInsuficiente,
                                                       "Estoque valido insuficiente");
    assert(!r.ok());
    assert(r.erro == Erro::EstoqueInsuficiente);
    assert(r.mensagem == "Estoque valido insuficiente");
}

void run_unit_tests_Resultado(void){
    unit_Resultado_construtor();
    unit_Resultado_ok();
    unit_Resultado_sucesso();
    unit_Resultado_falha();
}
