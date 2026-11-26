/**
 * @file produto.h
 * @brief Interface Produto e struct DadosProduto
 */
#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include "dinheiro.h"

/**
 * @brief Dados para cadastrar um produto
 * 
 */
struct DadosProduto {
    std::string codigo, nome, categoria;
    Dinheiro    custo;
    int         estoqueMinimo;
};

/**
 * @brief Produto do catalogo da rede
 * @details Cadastrado sem preco,o preco é definido dps e nao pode ficar abaixo do custo.
 *  A implementacao fica em produtoImpl
 *
 */
class Produto {
    public:
        virtual ~Produto(){} ///<Destrutor virtual

        virtual const std::string& codigo() const = 0; ///<Identificacao do produto
        virtual const std::string& nome() const = 0; ///<nome do produto
        virtual const std::string& categoria() const = 0; ///<categoria do produto
        virtual const Dinheiro& custo() const = 0; ///<custo de compra
        virtual const Dinheiro& preco() const = 0; ///<preco de venda 
        virtual int estoqueMinimo() const = 0; ///<qtd minima em estoque 


        virtual bool temPreco() const = 0; ///<True se o preco padrao ja foi definido
        virtual void setPreco(const Dinheiro& preco) = 0; ///<define o preco de venda do produto
};

#endif
