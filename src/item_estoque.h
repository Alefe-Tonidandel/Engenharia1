#ifndef ITEM_ESTOQUE_H
#define ITEM_ESTOQUE_H

#include <optional>
#include <string>
#include "data.h"

struct FiltroEstoque {
    std::optional<int> idUnidade;
    std::string categoria;
};

class ItemEstoque {
public:
    ItemEstoque();
    ItemEstoque(const std::string& codigoProduto, const std::string& nome,
                int quantidade, int quantidadeVencida, int estoqueMinimo,
                bool temValidade, const Data& validadeMaisProxima);
    ItemEstoque(const ItemEstoque& o);
    ItemEstoque& operator=(const ItemEstoque& o);
    ~ItemEstoque();

    const std::string& codigoProduto() const;
    const std::string& nome() const;
    int quantidade() const;
    int quantidadeVencida() const;
    int estoqueMinimo() const;
    bool temValidade() const;
    const Data& validadeMaisProxima() const;
    bool abaixoDoMinimo() const;

private:
    std::string codigoProduto_;
    std::string nome_;
    int quantidade_;
    int quantidadeVencida_;
    int estoqueMinimo_;
    bool temValidade_;
    Data validadeMaisProxima_;
};

#endif
