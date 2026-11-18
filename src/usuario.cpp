#include "usuario.h"

Usuario::Usuario()
    : id_(0), nome_(), perfil_(Perfil::OperadorCaixa), idUnidade_(0) {}
Usuario::Usuario(int id, const std::string& nome, Perfil perfil, int idUnidade)
    : id_(id), nome_(nome), perfil_(perfil), idUnidade_(idUnidade) {}
Usuario::Usuario(const Usuario& o)
    : id_(o.id_), nome_(o.nome_), perfil_(o.perfil_), idUnidade_(o.idUnidade_) {}
Usuario& Usuario::operator=(const Usuario& o) {
    if (this != &o) {
        id_ = o.id_; nome_ = o.nome_; perfil_ = o.perfil_; idUnidade_ = o.idUnidade_;
    }
    return *this;
}
Usuario::~Usuario() {}

int Usuario::id() const { return id_; }
const std::string& Usuario::nome() const { return nome_; }
Perfil Usuario::perfil() const { return perfil_; }
int Usuario::idUnidade() const { return idUnidade_; }

Sessao::Sessao() : usuario_() {}
Sessao::Sessao(const Usuario& u) : usuario_(u) {}
Sessao::Sessao(const Sessao& o) : usuario_(o.usuario_) {}
Sessao& Sessao::operator=(const Sessao& o) {
    if (this != &o) usuario_ = o.usuario_;
    return *this;
}
Sessao::~Sessao() {}

const Usuario& Sessao::usuario() const { return usuario_; }
