#ifndef BANCO_H
#define BANCO_H

#include <string>
#include <vector>
#include "produto.h"
#include "lote.h"
#include "venda.h"

// "Banco de dados" em memoria: guarda o catalogo, os lotes e as vendas.
// Os servicos recebem um Banco e trabalham em cima dele.
class Banco {
public:
    Banco();
    Banco(const Banco& o);
    Banco& operator=(const Banco& o);
    ~Banco();

    // catalogo
    Produto*       buscarProduto(const std::string& codigo);
    const Produto* buscarProduto(const std::string& codigo) const;
    void           adicionarProduto(const Produto& p);

    // lotes (o Banco gera o id sequencial)
    LoteEstoque adicionarLote(int idUnidade, const std::string& codigoProduto,
                              int quantidade, const Data& dataEntrada,
                              const Data& validade);
    std::vector<LoteEstoque>&       lotes();
    const std::vector<LoteEstoque>& lotes() const;
    const LoteEstoque*              buscarLote(int id) const;

    // soma dos saldos dos lotes ainda validos (nao vencidos) da unidade
    int saldoValido(int idUnidade, const std::string& codigoProduto,
                    const Data& hoje) const;

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
