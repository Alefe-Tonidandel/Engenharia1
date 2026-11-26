#include "sessao_impl.h"

SessaoImpl::SessaoImpl() : usuario_() {}
SessaoImpl::SessaoImpl(const Usuario& u) 
    : usuario_(u.id(), u.nome(), u.perfil(), u.idUnidade()) {}
SessaoImpl::SessaoImpl(const SessaoImpl& o) 
    : usuario_(o.usuario_) {}
SessaoImpl& SessaoImpl::operator=(const SessaoImpl& o) {
    if (this != &o) usuario_ = o.usuario_;
    return *this;
}
SessaoImpl::~SessaoImpl() {}

const Usuario& SessaoImpl::usuario() const { return usuario_; }