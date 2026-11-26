/**
 * @file venda_impl.h
 * @brief Declaracao da classe concreta VendaImpl
 * 
 */
#ifndef VENDA_IMPL_H
#define VENDA_IMPL_H

#include "venda.h"
#include <string>

/**
 * @brief Implementação concreta de venda 
 * 
 */
class VendaImpl : public Venda {
    public:
        VendaImpl();
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
        VendaImpl(int id, int idUnidade, const std::string& codigoProduto,
            int quantidade, const Dinheiro& valorTotal, const Data& data,
            int idUsuario);
        VendaImpl(const VendaImpl& o);
        VendaImpl& operator=(const VendaImpl& o);
        ~VendaImpl();

        int id() const override;
        int idUnidade() const override;
        const std::string& codigoProduto() const override;
        int quantidade() const override;
        const Dinheiro& valorTotal() const override;
        const Data& data() const override;
        int idUsuario() const override;

    private:
        int         id_, idUnidade_;
        std::string codigoProduto_;
        int         quantidade_;
        Dinheiro    valorTotal_;
        Data        data_;
        int         idUsuario_;
};

#endif
