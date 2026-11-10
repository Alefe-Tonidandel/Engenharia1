#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include "dinheiro.h"

// Dados de entrada para cadastrar um produto
struct DadosProduto {
    std::string codigo, nome, categoria;
    Dinheiro    custo;
    int         estoqueMinimo;
};

class Produto {
public:
    Produto();
    Produto(const std::string& codigo, const std::string& nome,
            const std::string& categoria, const Dinheiro& custo,
            int estoqueMinimo);
    Produto(const Produto& o);
    Produto& operator=(const Produto& o);
    ~Produto();

    const std::string& codigo() const;
    const std::string& nome() const;
    const std::string& categoria() const;
    const Dinheiro& custo() const;
    const Dinheiro& preco() const;
    int estoqueMinimo() const;

    bool temPreco() const;                 // produto recem-cadastrado nao tem
    void setPreco(const Dinheiro& preco);

private:
    std::string codigo_, nome_, categoria_;
    Dinheiro    custo_, preco_;
    int         estoqueMinimo_;
};

#endif
