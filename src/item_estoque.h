/**
 * @file item_estoque.h
 * @brief Declaracao da struct FiltroEstoque e da classe ItemEstoque usanas na consulta de estoque
 */
#ifndef ITEM_ESTOQUE_H
#define ITEM_ESTOQUE_H

#include <optional>
#include <string>
#include "data.h"

/**
 * @brief Filtro da consulta de estoque
 * @details Qual unidade e qual categoria deve ser feita a consulta
 */
struct FiltroEstoque {
    std::optional<int> idUnidade;
    std::string categoria;
};

/**
 * @brief Situacao do estoque de algum produto
 * 
 */
class ItemEstoque {
public:
    ItemEstoque();
    /**
     * @brief Cria um item da consulta de estoque 
     * 
     * @param codigoProduto Codigo do produto
     * @param nome Nome do produto
     * @param quantidade soma dos saldos dos lotes ainda validos
     * @param quantidadeVencida Soma dos lotes ja vencidos
     * @param estoqueMinimo qtd minima desejada em estoque
     * @param temValidade true se existe pelo menos um lote valido
     * @param validadeMaisProxima validade do lote valido que vence primeiro
     */
    ItemEstoque(const std::string& codigoProduto, const std::string& nome,
                int quantidade, int quantidadeVencida, int estoqueMinimo,
                bool temValidade, const Data& validadeMaisProxima);
    ItemEstoque(const ItemEstoque& o);
    ItemEstoque& operator=(const ItemEstoque& o);
    ~ItemEstoque();

    const std::string& codigoProduto() const;
    const std::string& nome() const;
    int quantidade() const;
    int quantidadeVencida() const;
    int estoqueMinimo() const;
    bool temValidade() const;
    const Data& validadeMaisProxima() const;
    bool abaixoDoMinimo() const;

private:
    std::string codigoProduto_;
    std::string nome_;
    int quantidade_;
    int quantidadeVencida_;
    int estoqueMinimo_;
    bool temValidade_;
    Data validadeMaisProxima_;
};

#endif
