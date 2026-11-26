/**
 * @file produto_impl.h
 * @brief Declaracao da ProdutoImpl, implementacao da interface Produto
 * 
 */

 #ifndef PRODUTO_IMPL_H
 #define PRODUTO_IMPL_H

 #include <string>
 #include "produto.h"

 /**
  * @brief Classe concreta de produto
  * 
  */
class ProdutoImpl : public Produto{
    public:
        ProdutoImpl(); ///<prod vazio
        /**
         * @brief Cria um produto sem preco de venda
         * 
         * @param codigo Identificação do produto
         * @param nome Nome do produto que queremos cadastrar
         * @param categoria De qual area o produto é
         * @param custo Custo de compra do produto
         * @param estoqueMinimo Valor minimo que temos que manter o produto em estoque
         */
        ProdutoImpl(const std::string& codigo, const std::string& nome, const std::string& categoria, const Dinheiro& custo, int estoqueMinimo);
        ProdutoImpl(const ProdutoImpl& o);
        ProdutoImpl& operator=(const ProdutoImpl& o);
        ~ProdutoImpl();

        const std::string& codigo() const override;
        const std::string& nome() const override;
        const std::string& categoria() const override;
        const Dinheiro& custo() const override;
        const Dinheiro& preco() const override;
        int estoqueMinimo() const override;

        bool temPreco() const override;                 // produto recem-cadastrado nao tem
        void setPreco(const Dinheiro& preco) override;

    private:
        std::string codigo_, nome_, categoria_;
        Dinheiro    custo_, preco_;
        int         estoqueMinimo_;
};

 #endif