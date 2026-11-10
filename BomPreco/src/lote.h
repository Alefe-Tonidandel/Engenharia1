#ifndef LOTE_H
#define LOTE_H

#include <string>
#include "data.h"

// Um lote de um produto na estoque de uma unidade, com validade propria.
class LoteEstoque {
public:
    LoteEstoque();
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

    bool vencido(const Data& hoje) const;   // vale ate o dia da validade
    void baixar(int quantidade);            // desconta do saldo

private:
    int         id_, idUnidade_;
    std::string codigoProduto_;
    int         quantidadeInicial_, saldo_;
    Data        dataEntrada_, validade_;
};

#endif
