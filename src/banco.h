/**
 * @file banco.h
 * @brief Interface banco - guarda produtos, lotes e vendas
 * 
 */
#ifndef BANCO_H
#define BANCO_H

#include <string>
#include "produto.h"
#include "lote.h"
#include "venda.h"

/**
 * @brief Banco de dados
 * @details Guarda catalogo, lotes e vendas. Os servicos recebem um banco e trabalham em cima dele
 * 
 */
class Banco {
    public:
        virtual ~Banco(){} ///<Destrutor virtual
        /**
         * @brief Busca um produto pelo codigo
         */
        virtual Produto* buscarProduto(const std::string& codigo) = 0;
        virtual const Produto* buscarProduto(const std::string& codigo) const = 0;
        virtual void adicionarProduto(const Produto& p) = 0;
        virtual int quantidadeProdutos() const = 0;
        virtual const Produto& produto(int i) const = 0;

        /**
         * @brief Cri e guarda um lote novo
         * 
         */
        virtual const LoteEstoque& adicionarLote(int idUnidade, const std::string& codigoProduto, int quantidade, const Data& dataEntrada, const Data& validade) = 0;
        virtual int quantidadeLotes() const = 0;
        virtual LoteEstoque& lote (int i) = 0;
        virtual const LoteEstoque& lote(int i) const = 0;
        virtual const LoteEstoque* buscarLote(int id) const = 0;


        /**
         * @brief Soma dos saldos dos lotes ainda validos de um produto 
         * 
         */
        virtual int saldoValido(int idUnidade, const std::string& codigoProduto, const Data& hoje) const = 0;

        /**
         * @brief Cria e guarda o reg de uma venda 
         * 
         */
        virtual const Venda& adicionarVenda(int idUnidade, const std::string& codigoProduto, int quantidade, const Dinheiro& valorTotal, const Data& data, int idUsuario) = 0;
        virtual int quantidadeVendas() const = 0;
        virtual const Venda& venda(int i) const = 0;
};

#endif
