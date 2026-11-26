/**
 * @file servico_cadastros_impl.h
 * @brief Declaracao de ServicoCadastrosImpl
 * 
 */

#ifndef SERVICO_CADASTROS_IMPL_H
#define SERVICO_CADASTROS_IMPL_H

#include "servico_cadastros.h"
#include "sessao.h"
#include "banco.h"

/**
 * @brief Impelementação concreta de servicoCadastros
 * @details Guarda ponteiros NAO-proprietarios para a Sessao e o Banco: copiar o
 *          servico copia os ponteiros, e o destrutor nao apaga nada.
 * 
 */
class ServicoCadastrosImpl : public ServicoCadastros {
public:
    ServicoCadastrosImpl();
    ServicoCadastrosImpl(const Sessao& sessao, Banco& banco);
    ServicoCadastrosImpl(const ServicoCadastrosImpl& o);
    ServicoCadastrosImpl& operator=(const ServicoCadastrosImpl& o);
    ~ServicoCadastrosImpl();

    Resultado<const Produto*> cadastrarProduto(const DadosProduto& dados) override;
    Resultado<const Produto*> definirPrecoPadrao(const std::string& codigo,
                                          const Dinheiro& preco) override;
private:
    bool podeGerirCatalogo() const;
    const Sessao* sessao_;
    Banco*        banco_;
};

#endif