/**
 * @file sessao_impl.h
 * @brief Declaracao de SessaoImpl, implementacao
 * 
 */

#ifndef SESSAO_IMPL_H
#define SESSAO_IMPL_H

#include "sessao.h"
#include "usuario_impl.h"

class SessaoImpl: public Sessao{
    public: 
        SessaoImpl(); ///<Sessao c usuario vazio
        explicit SessaoImpl(const Usuario& u);
        SessaoImpl(const SessaoImpl& o); ///<construtor de copia 
        SessaoImpl& operator=(const SessaoImpl& o); ///<operador de atribuicao
        ~SessaoImpl(); ///<destrutor

        const Usuario& usuario() const override;

    private:
        UsuarioImpl usuario_;///<Copia do usuario logado
};

#endif