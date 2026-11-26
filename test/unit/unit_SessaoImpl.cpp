/**
 * @file unit_SessaoImpl.cpp
 * @brief Testes unitarios da classe SessaoImpl
 * 
 */
#include "unit_SessaoImpl.h"
#include <cassert>
#include "../../src/sessao_impl.h"


void unit_SessaoImpl_construtor(void){
    SessaoImpl vazio;
    //chamar os getters de usuario
    assert(vazio.usuario().id() == 0 && vazio.usuario().nome().empty());

    UsuarioImpl pedro(31, "Pedro Alves", Perfil::OperadorCaixa, 1);
    SessaoImpl s(pedro); //abre a sessao do pedro
    assert(s.usuario().id() == 31 && s.usuario().nome() == "Pedro Alves" && s.usuario().perfil() == Perfil::OperadorCaixa && s.usuario().idUnidade() == 1);

}

void unit_SessaoImpl_copyConstrutor(void){
    UsuarioImpl joana(21, "Joana Reis", Perfil::RepositorEstoque, 1);
    SessaoImpl original(joana);
    SessaoImpl copia(original);

    assert(copia.usuario().id()==21 && copia.usuario().nome() == "Joana Reis" && copia.usuario().perfil() == Perfil::RepositorEstoque && copia.usuario().idUnidade() == 1);
}

void unit_SessaoImpl_operatorAtribuicao(void){
    UsuarioImpl joana(21, "Joana Reis", Perfil::RepositorEstoque, 1);
    SessaoImpl j(joana); 
    SessaoImpl s;
    s = j;
    assert(s.usuario().id()==21 && s.usuario().nome() == "Joana Reis" && s.usuario().perfil() == Perfil::RepositorEstoque && s.usuario().idUnidade() == 1);

}


void unit_SessaoImpl_destrutor(void){
    SessaoImpl* s = new SessaoImpl(UsuarioImpl(31, "Pedro Alves", Perfil::OperadorCaixa, 1));
    delete s;

}

void unit_SessaoImpl_usuario(void){
    UsuarioImpl pedro(31, "Pedro Alves", Perfil::OperadorCaixa, 1);
    SessaoImpl p(pedro);
    assert(p.usuario().id() == 31 && p.usuario().nome() == "Pedro Alves" && p.usuario().perfil() == Perfil::OperadorCaixa && p.usuario().idUnidade() == 1);
}

void run_unit_tests_SessaoImpl(void){
    unit_SessaoImpl_construtor();
    unit_SessaoImpl_copyConstrutor();
    unit_SessaoImpl_operatorAtribuicao();
    unit_SessaoImpl_destrutor();
    unit_SessaoImpl_usuario();
}