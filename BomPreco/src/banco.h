/**
 * @file banco.h
 * @brief Declaração da classe Banco, que guarda produtos, lotes e vendas em memoria
 */
#ifndef BANCO_H
#define BANCO_H

#include <string>
#include <vector>
#include "produto.h"
#include "lote.h"
#include "venda.h"

/**
 * @brief Banco de dados
 * @details Guarda o catalogo, os lotes e as vendas.
 */

// Os servicos recebem um Banco e trabalham em cima dele.
class Banco {
public:
    /**
     * @brief Cria um banco vazio
     * 
    */
    Banco();
    Banco(const Banco& o);
    Banco& operator=(const Banco& o);
    ~Banco();

    // catalogo
    /**
     * @brief Busca um produto pelo código
     * 
     * @param codigo Identificação do produto
     * @return Ponteiro para o produto ou nullptr se nao existir 
    */
    Produto*       buscarProduto(const std::string& codigo);
    const Produto* buscarProduto(const std::string& codigo) const;
    void           adicionarProduto(const Produto& p);

    // lotes (o Banco gera o id sequencial)
    /**
     * @brief Cria um novo lote
     * 
     * @param idUnidade Unidade que recebeu o lote
     * @param codigoProduto Produto do lote 
     * @param quantidade Quantidade que esta entrando
     * @param dataEntrada Quando chegou
     * @param validade Quando vence
     * @return Lote criado
    */
    LoteEstoque adicionarLote(int idUnidade, const std::string& codigoProduto,
                              int quantidade, const Data& dataEntrada,
                              const Data& validade);
    std::vector<LoteEstoque>&       lotes();
    const std::vector<LoteEstoque>& lotes() const;
    const LoteEstoque*              buscarLote(int id) const;

    /**
     * @brief Saldos validos
     * @details Soma dos saldos ainda válidos pra saber a quantidade disponivel
     * @param idUnidade Onde estamos querendo saber
     * @param codigoProduto Qual produto queremos achar 
     * @param hoje Data atual para calcular o vencimento
     * @return Soma dos saldos dos lotes não vencidos
    */
    // soma dos saldos dos lotes ainda validos (nao vencidos) da unidade
    int saldoValido(int idUnidade, const std::string& codigoProduto,
                    const Data& hoje) const;


    /**
     * @brief Registrar uma venda
     * 
     * @param idUnidade De onde foi a venda
     * @param codigoProduto Qual produto foi vendido
     * @param quantidade Quantos produtos foram vendidos
     * @param valorTotal Soma da compra 
     * @param data Data da venda
     * @param idUsuario Quem vendeu
     * @return Venda criada
     */
    // vendas (o Banco gera o id sequencial)
    Venda adicionarVenda(int idUnidade, const std::string& codigoProduto,
                         int quantidade, const Dinheiro& valorTotal,
                         const Data& data, int idUsuario);
    const std::vector<Venda>& vendas() const;

private:
    std::vector<Produto>     produtos_;
    std::vector<LoteEstoque> lotes_;
    std::vector<Venda>       vendas_;
    int proximoIdLote_, proximoIdVenda_;
};

#endif
