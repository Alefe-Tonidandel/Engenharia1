/**
 * @file usuario_impl.h
 * @brief Declaracao da classe UsuarioImpl, implementacao da interface Usuario
 */
#ifndef USUARIO_IMPL_H
#define USUARIO_IMPL_H

#include <string>
#include "usuario.h"

/**
 * @brief Classe concreta de usuario 
 * 
 */
class UsuarioImpl : public Usuario{ 
    public:
        UsuarioImpl();
        /**
         * @brief Cria um usuario
         * 
         * @param id Identificacao do usuario
         * @param nome Nome do usuario
         * @param perfil Funcao dentro da unidade
         * @param idUnidade Unidade em que ele trabalha. O gestor não é vinculado a unidade 
         */
        UsuarioImpl(int id, const std::string& nome, Perfil perfil, int idUnidade);
        UsuarioImpl(const UsuarioImpl& o); ///<Construtor de copia
        UsuarioImpl& operator=(const UsuarioImpl& o);///<Operador de atribuicao
        ~UsuarioImpl();///<Destrutor

        int id() const override;
        const std::string& nome() const override;
        Perfil perfil() const override;
        int idUnidade() const override;

    private:
        int         id_;
        std::string nome_;
        Perfil      perfil_;
        int         idUnidade_;

};

#endif 