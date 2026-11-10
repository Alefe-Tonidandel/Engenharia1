#ifndef SERVICO_CADASTROS_H
#define SERVICO_CADASTROS_H

#include <string>
#include "tipos.h"
#include "usuario.h"
#include "produto.h"
#include "banco.h"

// Catalogo padrao da rede. Apenas Gestor da Rede / Administrador.
// Guarda ponteiros NAO-proprietarios para a Sessao e o Banco: copiar o
// servico copia os ponteiros, e o destrutor nao apaga nada.
class ServicoCadastros {
public:
    ServicoCadastros();
    ServicoCadastros(const Sessao& sessao, Banco& banco);
    ServicoCadastros(const ServicoCadastros& o);
    ServicoCadastros& operator=(const ServicoCadastros& o);
    ~ServicoCadastros();

    Resultado<Produto> cadastrarProduto(const DadosProduto& dados);
    Resultado<Produto> definirPrecoPadrao(const std::string& codigo,
                                          const Dinheiro& preco);
private:
    bool podeGerirCatalogo() const;
    const Sessao* sessao_;
    Banco*        banco_;
};

#endif
