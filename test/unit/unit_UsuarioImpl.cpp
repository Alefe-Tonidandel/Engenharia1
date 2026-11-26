/**
 * @file unit_UsuarioImpl.cpp
 * @brief Testes unitarios da classe UsuarioImpl
 * 
 */
#include <cassert>
#include "unit_UsuarioImpl.h"
#include "../../src/usuario_impl.h"

void unit_UsuarioImpl_construtor(void){
    UsuarioImpl vazio;
    assert(vazio.id() == 0 && vazio.nome().empty());
    assert(vazio.perfil() == Perfil::OperadorCaixa && vazio.idUnidade() == 0);

    UsuarioImpl pedro(31, "Pedro Alves", Perfil::OperadorCaixa, 1);
    assert(pedro.id() == 31 && pedro.nome() == "Pedro Alves" && pedro.perfil() == Perfil::OperadorCaixa && pedro.idUnidade() == 1);

}

void unit_UsuarioImpl_copyConstrutor(void){
    UsuarioImpl joana(21, "Joana Reis", Perfil::RepositorEstoque, 1);
    UsuarioImpl copia(joana);

    assert(copia.id()==21 && copia.nome() == "Joana Reis" && copia.perfil() == Perfil::RepositorEstoque && copia.idUnidade() == 1);
}

void unit_UsuarioImpl_operatorAtribuicao(void){
    UsuarioImpl rafael(10, "Rafa lima", Perfil::GestorRede, 0);
    UsuarioImpl u;
    u = rafael;

    assert(u.id()==10 && u.nome() == "Rafa lima" && u.perfil() == Perfil::GestorRede && u.idUnidade() == 0);
}

void unit_UsuarioImpl_destrutor(void) {
    UsuarioImpl* u = new UsuarioImpl(31, "pedro alves", Perfil::OperadorCaixa, 1);
    delete u;
}

void unit_UsuarioImpl_id(void) {
    UsuarioImpl joana(21, "Joana Reis", Perfil::RepositorEstoque, 1);
    assert(joana.id() == 21);
}


void unit_UsuarioImpl_nome(void){
    UsuarioImpl joana(21, "Joana Reis", Perfil::RepositorEstoque, 1);
    assert(joana.nome() == "Joana Reis");

}

void unit_UsuarioImpl_perfil(void){
    UsuarioImpl joana(21, "Joana Reis", Perfil::RepositorEstoque, 1);
    UsuarioImpl pedro(31, "pedro alves", Perfil::OperadorCaixa, 1);
    UsuarioImpl rafael(10, "Rafa lima", Perfil::GestorRede, 0);

    assert(rafael.perfil() == Perfil::GestorRede);
    assert(joana.perfil() == Perfil::RepositorEstoque);
    assert(pedro.perfil() == Perfil::OperadorCaixa);
}

void unit_UsuarioImpl_idUnidade(void){
    UsuarioImpl rafael(10, "Rafa lima", Perfil::GestorRede, 0);
    UsuarioImpl joana(21, "Joana Reis", Perfil::RepositorEstoque, 1);
    assert(rafael.idUnidade() == 0);
    assert(joana.idUnidade() == 1);

}

void run_unit_tests_UsuarioImpl(void){
    unit_UsuarioImpl_construtor();
    unit_UsuarioImpl_copyConstrutor();
    unit_UsuarioImpl_operatorAtribuicao();
    unit_UsuarioImpl_destrutor();
    unit_UsuarioImpl_id();
    unit_UsuarioImpl_nome();
    unit_UsuarioImpl_perfil();
    unit_UsuarioImpl_idUnidade();
}
