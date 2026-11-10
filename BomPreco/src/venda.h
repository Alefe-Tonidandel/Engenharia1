#ifndef VENDA_H
#define VENDA_H

#include <string>
#include "data.h"
#include "dinheiro.h"

class Venda {
public:
    Venda();
    Venda(int id, int idUnidade, const std::string& codigoProduto,
          int quantidade, const Dinheiro& valorTotal, const Data& data,
          int idUsuario);
    Venda(const Venda& o);
    Venda& operator=(const Venda& o);
    ~Venda();

    int id() const;
    int idUnidade() const;
    const std::string& codigoProduto() const;
    int quantidade() const;
    const Dinheiro& valorTotal() const;
    const Data& data() const;
    int idUsuario() const;

private:
    int         id_, idUnidade_;
    std::string codigoProduto_;
    int         quantidade_;
    Dinheiro    valorTotal_;
    Data        data_;
    int         idUsuario_;
};

#endif
