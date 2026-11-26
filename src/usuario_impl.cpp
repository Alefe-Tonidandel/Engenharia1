#include "usuario_impl.h"

UsuarioImpl::UsuarioImpl()
    : id_(0), nome_(), perfil_(Perfil::OperadorCaixa), idUnidade_(0) {}
UsuarioImpl::UsuarioImpl(int id, const std::string& nome, Perfil perfil, int idUnidade)
    : id_(id), nome_(nome), perfil_(perfil), idUnidade_(idUnidade) {}
UsuarioImpl::UsuarioImpl(const UsuarioImpl& o)
    : Usuario(), id_(o.id_), nome_(o.nome_), perfil_(o.perfil_), idUnidade_(o.idUnidade_) {}
UsuarioImpl& UsuarioImpl::operator=(const UsuarioImpl& o) {
    if (this != &o) {
        id_ = o.id_; nome_ = o.nome_; perfil_ = o.perfil_; idUnidade_ = o.idUnidade_;
    }
    return *this;
}
UsuarioImpl::~UsuarioImpl() {}

int UsuarioImpl::id() const {
    return id_;
}
const std::string& UsuarioImpl::nome() const {
    return nome_;
}
Perfil UsuarioImpl::perfil() const {
    return perfil_;
}
int UsuarioImpl::idUnidade() const {
    return idUnidade_;
}


