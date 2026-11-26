/**
 * @file usuario.h
 * @brief Interface Usuario
 */
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "tipos.h"

/**
 * @brief Funcionario que usa o sistema
 * @details Cada usuario possui sua identificação e acessos diferentes dependendo da sua função
 * A implementação fica em UsuarioImpl
 * 
 */
//sprint 6- usuario agr so tem a interface 
class Usuario {
public:
    virtual ~Usuario(){} ///<Destrutor virtual
    virtual int id() const = 0; ///<Identificacao do usuario 
    virtual const std::string& nome() const = 0; ///<Nome do usuario
    virtual Perfil perfil() const = 0; ///<Função do usuario
    virtual int idUnidade() const = 0; ///Unidade (0 = nao vinculado - gestor da rede)
};

#endif