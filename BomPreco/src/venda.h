/**
 * @file venda.h
 * @brief Declaracao da classe Venda 
 */
#ifndef VENDA_H
#define VENDA_H

#include <string>
#include "data.h"
#include "dinheiro.h"

/**
 * @brief Venda
 * @details Registrar uma venda de algum produto em uma unidade
 * 
 */
class Venda {
public:
    Venda();
    /**
     * @brief Cria o registro de uma venda
     * 
     * @param id Identificador da venda 
     * @param idUnidade Unidade
     * @param codigoProduto Codigo do produto
     * @param quantidade Quantidade vendida
     * @param valorTotal Valor total da venda
     * @param data Dia da venda
     * @param idUsuario Quem realizou a venda
     */
    Venda(int id, int idUnidade, const std::string& codigoProduto,
          int quantidade, const Dinheiro& valorTotal, const Data& data,
          int idUsuario);
    Venda(const Venda& o);
    Venda& operator=(const Venda& o);
    ~Venda();

    int id() const;
    int idUnidade() const;
    const std::string& codigoProduto() const;
    int quantidade() const;
    const Dinheiro& valorTotal() const;
    const Data& data() const;
    int idUsuario() const;

private:
    int         id_, idUnidade_;
    std::string codigoProduto_;
    int         quantidade_;
    Dinheiro    valorTotal_;
    Data        data_;
    int         idUsuario_;
};

#endif
