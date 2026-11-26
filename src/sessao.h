/**
 * @file sessao.h
 * @brief Interface Sessao
 * 
 */
#ifndef SESSAO_H
#define SESSAO_H

#include "usuario.h"

/**
 * @brief Sessao do usuario logado
 * @details Os servicos consultam a Sessao pra saber o perfil e a unidade 
 * 
 */
class Sessao {
public:
    virtual ~Sessao() {} ///<Destrutor virtual
    virtual const Usuario& usuario() const = 0;
};


#endif 