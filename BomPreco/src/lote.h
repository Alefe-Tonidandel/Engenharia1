/**
 * @file lote.h
 * @brief Declaração da classe LoteEstoque
 */
#ifndef LOTE_H
#define LOTE_H

#include <string>
#include "data.h"

/**
 * @brief Lote de um produto
 * @details Lote do estoque de algum produto na unidade, com validade propria
 * 
 */
class LoteEstoque {
public:
    LoteEstoque();
    /**
     * @brief Construct a new Lote Estoque object
     * 
     * @param id Identificação do lote
     * @param idUnidade Unidade que estamos dando entrada 
     * @param codigoProduto Codigo de identificação do produto
     * @param quantidade Quantidade que esta chegando
     * @param dataEntrada Data de recebimento
     * @param validade Validade do lote 
     */
    LoteEstoque(int id, int idUnidade, const std::string& codigoProduto,
                int quantidade, const Data& dataEntrada, const Data& validade);
    LoteEstoque(const LoteEstoque& o);
    LoteEstoque& operator=(const LoteEstoque& o);
    ~LoteEstoque();

    int id() const;
    int idUnidade() const;
    const std::string& codigoProduto() const;
    int quantidadeInicial() const;
    int saldo() const;
    const Data& dataEntrada() const;
    const Data& validade() const;
    /**
     * @brief Diz se o lote ja venceu
     * 
     * @param hoje  Data de referencia
     * @return true se hoje for depois da validade
     */
    bool vencido(const Data& hoje) const;   // vale ate o dia da validade
    /**
     * @brief Desconta uma quantidade do saldo do lote
     * 
     * @param quantidade Quantidade retirada
     */
    void baixar(int quantidade);            // desconta do saldo

private:
    int         id_, idUnidade_;
    std::string codigoProduto_;
    int         quantidadeInicial_, saldo_;
    Data        dataEntrada_, validade_;
};

#endif
