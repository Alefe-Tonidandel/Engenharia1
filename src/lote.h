/**
 * @file lote.h
 * @brief Interface LoteEstoque
 */
#ifndef LOTE_H
#define LOTE_H

#include <string>
#include "data.h"
/**
 * @brief Lote de um produto
 * @details Lote do estoque de algum produto na unidade, com validade propria. 
 * A implementação esta em loteEstoqueImpl
 * 
 */
class LoteEstoque {
public:
    virtual ~LoteEstoque(){} ///<Destrutor virtual
    virtual int id() const = 0; ///< Identificacao do lote
    virtual int idUnidade() const = 0; ///<Unidade do lote
    virtual const std::string& codigoProduto() const = 0;///<Codigo do produto do lote
    virtual int quantidadeInicial() const = 0; ///<Qtd que chegou
    virtual int saldo() const = 0; ///<Qtd que ainda resta
    virtual const Data& dataEntrada() const = 0; ///<Data recebimento
    virtual const Data& validade() const = 0; ///<Validade do lote

    /**
     * @brief Diz de o lote ja venceu
     * 
     * @param hoje Data de referencia
     * @return true se hoje for dps da validade
     */
    virtual bool vencido(const Data& hoje) const = 0;

    /**
     * @brief Desconta uma qtd do saldo do lote
     * 
     * @param quantidade Quantidade vendida/vencida pra retirar 
     */
    virtual void baixar(int quantidade) = 0;

};

#endif
