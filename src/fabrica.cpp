#include "fabrica.h"
#include "banco_impl.h"
#include "usuario_impl.h"
#include "sessao_impl.h"
#include "servico_cadastros_impl.h"
#include "servico_estoque_impl.h"

Fabrica::Fabrica() {}
Fabrica::Fabrica(const Fabrica& o) { (void)o; }
Fabrica& Fabrica::operator=(const Fabrica& o) { (void)o; return *this; }
Fabrica::~Fabrica() {}

Banco* Fabrica::criarBanco() {
    return new BancoImpl();
}

Usuario* Fabrica::criarUsuario(int id, const std::string& nome, Perfil perfil, int idUnidade) {
    return new UsuarioImpl(id, nome, perfil, idUnidade);
}

Sessao* Fabrica::criarSessao(const Usuario& u) {
    return new SessaoImpl(u);
}

ServicoCadastros* Fabrica::criarServicoCadastros(const Sessao& sessao, Banco& banco) {
    return new ServicoCadastrosImpl(sessao, banco);
}

ServicoEstoque* Fabrica::criarServicoEstoque(const Sessao& sessao, Banco& banco) {
    return new ServicoEstoqueImpl(sessao, banco);
}
