/**
 * @file servico_cadastros.h
 * @brief Declaracao do ServicoCadastros - cadastro de produtos e precos
 */
#ifndef SERVICO_CADASTROS_H
#define SERVICO_CADASTROS_H

#include <string>
#include "tipos.h"
#include "usuario.h"
#include "produto.h"
#include "banco.h"

// Guarda ponteiros NAO-proprietarios para a Sessao e o Banco: copiar o
// servico copia os ponteiros, e o destrutor nao apaga nada.
/**
 * @brief Servico de cadastros de produtos
 * @details Catalogo da rede fica disponivel apenas para o gestor da rede e administrador
 * 
 */
class ServicoCadastros {
public:
    ServicoCadastros();
    /**
     * @brief Cria novo servico ligado a uma sessao e a um banco
     * 
     * @param sessao  Usuario logado
     * @param banco Onde os produtos são gravados
     */
    ServicoCadastros(const Sessao& sessao, Banco& banco);
    ServicoCadastros(const ServicoCadastros& o);
    ServicoCadastros& operator=(const ServicoCadastros& o);
    ~ServicoCadastros();
    /**
     * @brief Cadastra um novo produto no catalogo, ainda sem preco de venda
     * 
     * @param dados Codigo, nome, categoria, custo e estoque minimo
     * @return Resultado<Produto> 
     */
    Resultado<Produto> cadastrarProduto(const DadosProduto& dados);
    /**
     * @brief Define o preco de venda padrao de um produto
     * 
     * @param codigo Codigo do produto
     * @param preco Novo preco - não pode ser menor que o custo
     * @return Resultado<Produto> 
     */
    Resultado<Produto> definirPrecoPadrao(const std::string& codigo,
                                          const Dinheiro& preco);
private:
    bool podeGerirCatalogo() const;
    const Sessao* sessao_;
    Banco*        banco_;
};

#endif
