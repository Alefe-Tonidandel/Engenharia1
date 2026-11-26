#include "produto_impl.h"

ProdutoImpl::ProdutoImpl()
    : codigo_(), nome_(), categoria_(), custo_(), preco_(), estoqueMinimo_(0) {}
ProdutoImpl::ProdutoImpl(const std::string& codigo, const std::string& nome,
                 const std::string& categoria, const Dinheiro& custo,
                 int estoqueMinimo)
    : codigo_(codigo), nome_(nome), categoria_(categoria),
      custo_(custo), preco_(), estoqueMinimo_(estoqueMinimo) {}
ProdutoImpl::ProdutoImpl(const ProdutoImpl& o)
    : Produto(), codigo_(o.codigo_), nome_(o.nome_), categoria_(o.categoria_),
      custo_(o.custo_), preco_(o.preco_), estoqueMinimo_(o.estoqueMinimo_) {}
ProdutoImpl& ProdutoImpl::operator=(const ProdutoImpl& o) {
    if (this != &o) {
        codigo_ = o.codigo_; nome_ = o.nome_; categoria_ = o.categoria_;
        custo_ = o.custo_; preco_ = o.preco_; estoqueMinimo_ = o.estoqueMinimo_;
    }
    return *this;
}
ProdutoImpl::~ProdutoImpl() {}

const std::string& ProdutoImpl::codigo() const { return codigo_; }
const std::string& ProdutoImpl::nome() const { return nome_; }
const std::string& ProdutoImpl::categoria() const { return categoria_; }
const Dinheiro& ProdutoImpl::custo() const { return custo_; }
const Dinheiro& ProdutoImpl::preco() const { return preco_; }
int ProdutoImpl::estoqueMinimo() const { return estoqueMinimo_; }

bool ProdutoImpl::temPreco() const { return preco_.centavos() > 0; }
void ProdutoImpl::setPreco(const Dinheiro& preco) { preco_ = preco; }
