/**
 * @file lote_impl.h
 * @brief Declaracao da classe LoteEstoqueImpl, implementacao da interface LoteEstoque
 * 
 */
#ifndef LOTE_IMPL_H
#define LOTE_IMPL_H

#include <string>
#include "lote.h"

/**
 * @brief Classe concreta LoteEstoque
 * 
 */
class LoteEstoqueImpl : public LoteEstoque {
    public:
        LoteEstoqueImpl();
        /**
         * @brief Cria um lote
         * 
         * @param id Identificação do lote
         * @param idUnidade Unidade que estamos dando entrada 
         * @param codigoProduto Codigo de identificação do produto
         * @param quantidade Quantidade que esta chegando
         * @param dataEntrada Data de recebimento
         * @param validade Validade do lote 
         */
        LoteEstoqueImpl(int id, int idUnidade, const std::string& codigoProduto, int quantidade, const Data& dataEntrada, const Data& validade);
        LoteEstoqueImpl(const LoteEstoqueImpl& o);
        LoteEstoqueImpl& operator=(const LoteEstoqueImpl& o);
        ~LoteEstoqueImpl();

        int id() const override;
        int idUnidade() const override;
        const std::string& codigoProduto() const override;
        int quantidadeInicial() const override;
        int saldo() const override;
        const Data& dataEntrada() const override;
        const Data& validade() const override;
        
        bool vencido(const Data& hoje) const override;   // vale ate o dia da validade
        void baixar(int quantidade) override;            // desconta do saldo

    private:
        int         id_, idUnidade_;
        std::string codigoProduto_;
        int         quantidadeInicial_, saldo_;
        Data        dataEntrada_, validade_;
};

#endif 