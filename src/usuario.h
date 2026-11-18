#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "tipos.h"

class Usuario {
public:
    Usuario();
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

// A Sessao guarda quem esta logado; os servicos consultam a Sessao
// para saber o perfil e a unidade (quem chama nao "escolhe" a unidade).
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
