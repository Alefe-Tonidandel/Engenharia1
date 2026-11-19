/**
 * @file produto.h
 * @brief Declaracao da classe Produto e da struct DadosProduto
 */
#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include "dinheiro.h"

/**
 * @brief Dados do produto
 * @details Dados para cadastrar um produto
 * 
 */
struct DadosProduto {
    std::string codigo, nome, categoria;
    Dinheiro    custo;
    int         estoqueMinimo;
};

/**
 * @brief Produto do catalogo da rede
 * @details É cadastrado sem preco, o preco padrao é definido depois e nao pode ficar abaixo do custo
 * 
 */
class Produto {
public:
    Produto();
    /**
     * @brief Cria um produto sem preco de venda
     * 
     * @param codigo Identificação do produto
     * @param nome Nome do produto que queremos cadastrar
     * @param categoria De qual area o produto é
     * @param custo Custo de compra do produto
     * @param estoqueMinimo Valor minimo que temos que manter o produto em estoque
     */
    Produto(const std::string& codigo, const std::string& nome,
            const std::string& categoria, const Dinheiro& custo,
            int estoqueMinimo);
    Produto(const Produto& o);
    Produto& operator=(const Produto& o);
    ~Produto();

    const std::string& codigo() const;
    const std::string& nome() const;
    const std::string& categoria() const;
    const Dinheiro& custo() const;
    const Dinheiro& preco() const;
    int estoqueMinimo() const;

    bool temPreco() const;                 // produto recem-cadastrado nao tem
    void setPreco(const Dinheiro& preco);

private:
    std::string codigo_, nome_, categoria_;
    Dinheiro    custo_, preco_;
    int         estoqueMinimo_;
};

#endif
