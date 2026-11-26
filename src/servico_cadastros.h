/**
 * @file servico_cadastros.h
 * @brief Interface ServicosCadastros - cadastro de produtos e preco
 */
#ifndef SERVICO_CADASTROS_H
#define SERVICO_CADASTROS_H

#include <string>
#include "tipos.h"
#include "produto.h"

/**
 * @brief Servico de cadastros de produtos e precos
 * @details Catalogo da rede fica disponivel apenas para o gestor da rede e administrador
 * 
 */
class ServicoCadastros {
public:
    virtual ~ServicoCadastros(){}
    virtual Resultado<const Produto*> cadastrarProduto(const DadosProduto& dados) = 0;
    virtual Resultado<const Produto*> definirPrecoPadrao(const std::string& codigo, const Dinheiro& preco) = 0;
};

#endif
