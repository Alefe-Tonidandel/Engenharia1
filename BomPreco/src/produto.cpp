#include "produto.h"

Produto::Produto()
    : codigo_(), nome_(), categoria_(), custo_(), preco_(), estoqueMinimo_(0) {}
Produto::Produto(const std::string& codigo, const std::string& nome,
                 const std::string& categoria, const Dinheiro& custo,
                 int estoqueMinimo)
    : codigo_(codigo), nome_(nome), categoria_(categoria),
      custo_(custo), preco_(), estoqueMinimo_(estoqueMinimo) {}
Produto::Produto(const Produto& o)
    : codigo_(o.codigo_), nome_(o.nome_), categoria_(o.categoria_),
      custo_(o.custo_), preco_(o.preco_), estoqueMinimo_(o.estoqueMinimo_) {}
Produto& Produto::operator=(const Produto& o) {
    if (this != &o) {
        codigo_ = o.codigo_; nome_ = o.nome_; categoria_ = o.categoria_;
        custo_ = o.custo_; preco_ = o.preco_; estoqueMinimo_ = o.estoqueMinimo_;
    }
    return *this;
}
Produto::~Produto() {}

const std::string& Produto::codigo() const { return codigo_; }
const std::string& Produto::nome() const { return nome_; }
const std::string& Produto::categoria() const { return categoria_; }
const Dinheiro& Produto::custo() const { return custo_; }
const Dinheiro& Produto::preco() const { return preco_; }
int Produto::estoqueMinimo() const { return estoqueMinimo_; }

bool Produto::temPreco() const { return preco_.centavos() > 0; }
void Produto::setPreco(const Dinheiro& preco) { preco_ = preco; }
