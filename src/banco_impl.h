/**
 * @file banco_impl.h
 * @brief Declaracao de BancoImpl
 * 
 */
#ifndef BANCO_IMPL_H
#define BANCO_IMPL_H

#include <string>
#include <vector>
#include "banco.h"
#include "produto_impl.h"
#include "lote_impl.h"
#include "venda_impl.h"

/**
 * @brief Implementacao concretade banco q guarda em memoria
 * @details Guarda as classes concretas em vetores e devolve as interfaces
 */

// Os servicos recebem um Banco e trabalham em cima dele.
class BancoImpl : public Banco {
public:
    BancoImpl();
    BancoImpl(const BancoImpl& o);
    BancoImpl& operator=(const BancoImpl& o);
    ~BancoImpl();


    Produto* buscarProduto(const std::string& codigo) override;
    const Produto* buscarProduto(const std::string& codigo) const override;
    void adicionarProduto(const Produto& p) override;
    int quantidadeProdutos() const override;
    const Produto& produto(int i) const override;

    const LoteEstoque& adicionarLote(int idUnidade, const std::string& codigoProduto,
                              int quantidade, const Data& dataEntrada,
                              const Data& validade) override;
    int quantidadeLotes() const override;
    LoteEstoque& lote(int i) override;
    const LoteEstoque& lote (int i) const override;
    const LoteEstoque* buscarLote(int id) const override;

    int saldoValido(int idUnidade, const std::string& codigoProduto,
                    const Data& hoje) const override;


    const Venda& adicionarVenda(int idUnidade, const std::string& codigoProduto,
                         int quantidade, const Dinheiro& valorTotal,
                         const Data& data, int idUsuario) override;
    int quantidadeVendas() const override;
    const Venda& venda(int i) const override;

private:
    std::vector<ProdutoImpl> produtos_; ///<catalogo
    std::vector<LoteEstoqueImpl> lotes_; ///<lotes
    std::vector<VendaImpl>       vendas_; ///<vendas
    int proximoIdLote_, proximoIdVenda_; ///<proximo id de lote e id de venda 
};

#endif