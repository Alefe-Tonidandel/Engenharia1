#include "item_estoque.h"

ItemEstoque::ItemEstoque()
    : codigoProduto_(), nome_(), quantidade_(0), quantidadeVencida_(0),
      estoqueMinimo_(0), temValidade_(false), validadeMaisProxima_() {}

ItemEstoque::ItemEstoque(const std::string& codigoProduto, const std::string& nome,
                         int quantidade, int quantidadeVencida, int estoqueMinimo,
                         bool temValidade, const Data& validadeMaisProxima)
    : codigoProduto_(codigoProduto), nome_(nome), quantidade_(quantidade),
      quantidadeVencida_(quantidadeVencida), estoqueMinimo_(estoqueMinimo),
      temValidade_(temValidade), validadeMaisProxima_(validadeMaisProxima) {}

ItemEstoque::ItemEstoque(const ItemEstoque& o)
    : codigoProduto_(o.codigoProduto_), nome_(o.nome_),
      quantidade_(o.quantidade_), quantidadeVencida_(o.quantidadeVencida_),
      estoqueMinimo_(o.estoqueMinimo_), temValidade_(o.temValidade_),
      validadeMaisProxima_(o.validadeMaisProxima_) {}

ItemEstoque& ItemEstoque::operator=(const ItemEstoque& o) {
    if (this != &o) {
        codigoProduto_ = o.codigoProduto_;
        nome_ = o.nome_;
        quantidade_ = o.quantidade_;
        quantidadeVencida_ = o.quantidadeVencida_;
        estoqueMinimo_ = o.estoqueMinimo_;
        temValidade_ = o.temValidade_;
        validadeMaisProxima_ = o.validadeMaisProxima_;
    }
    return *this;
}

ItemEstoque::~ItemEstoque() {}

const std::string& ItemEstoque::codigoProduto() const { return codigoProduto_; }
const std::string& ItemEstoque::nome() const { return nome_; }
int ItemEstoque::quantidade() const { return quantidade_; }
int ItemEstoque::quantidadeVencida() const { return quantidadeVencida_; }
int ItemEstoque::estoqueMinimo() const { return estoqueMinimo_; }
bool ItemEstoque::temValidade() const { return temValidade_; }
const Data& ItemEstoque::validadeMaisProxima() const { return validadeMaisProxima_; }
bool ItemEstoque::abaixoDoMinimo() const { return quantidade_ < estoqueMinimo_; }
