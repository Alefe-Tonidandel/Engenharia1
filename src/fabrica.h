#ifndef FABRICA_H
#define FABRICA_H

#include "banco.h"
#include "sessao.h"
#include "usuario.h"
#include "servico_cadastros.h"
#include "servico_estoque.h"

class Fabrica {
public:
    Fabrica();
    Fabrica(const Fabrica& o);
    Fabrica& operator=(const Fabrica& o);
    ~Fabrica();

    Banco* criarBanco();
    Sessao* criarSessao(const Usuario& u);
    ServicoCadastros* criarServicoCadastros(const Sessao& sessao, Banco& banco);
    ServicoEstoque* criarServicoEstoque(const Sessao& sessao, Banco& banco);
};

#endif
