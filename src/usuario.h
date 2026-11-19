/**
 * @file usuario.h
 * @brief Declaracao das classes Usuario e Sessao
 */
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "tipos.h"

/**
 * @brief Funcionario que usa o sistema
 * @details Cada usuario possui sua identificação e acessos diferentes dependendo da sua função
 * 
 */
class Usuario {
public:
    Usuario();
    /**
     * @brief Cria um usuario
     * 
     * @param id Identificação do usuário
     * @param nome Nome do usuário
     * @param perfil Sua função dentro da unidade
     * @param idUnidade Unidade em que o usuário trabalha. O gestor não é vinculado a unidade
     */
    Usuario(int id, const std::string& nome, Perfil perfil, int idUnidade);
    Usuario(const Usuario& o);
    Usuario& operator=(const Usuario& o);
    ~Usuario();

    int id() const;
    const std::string& nome() const;
    Perfil perfil() const;
    int idUnidade() const;          // 0 = nao vinculado a uma unidade (Gestor)

private:
    int         id_;
    std::string nome_;
    Perfil      perfil_;
    int         idUnidade_;
};

// os servicos consultam a Sessao para saber o perfil e a unidade (quem chama nao "escolhe" a unidade).
/**
 * @brief Abre uma sessao para o usuario logado 
 * 
 */
class Sessao {
public:
    Sessao();
    explicit Sessao(const Usuario& u);
    Sessao(const Sessao& o);
    Sessao& operator=(const Sessao& o);
    ~Sessao();

    const Usuario& usuario() const;

private:
    Usuario usuario_;
};

#endif
