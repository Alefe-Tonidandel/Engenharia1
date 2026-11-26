#include "banco_impl.h"

BancoImpl::BancoImpl() : produtos_(), lotes_(), vendas_(),
                 proximoIdLote_(1), proximoIdVenda_(1) {}
BancoImpl::BancoImpl(const BancoImpl& o)
    : Banco(), produtos_(o.produtos_), lotes_(o.lotes_), vendas_(o.vendas_),
      proximoIdLote_(o.proximoIdLote_), proximoIdVenda_(o.proximoIdVenda_) {}
BancoImpl& BancoImpl::operator=(const BancoImpl& o) {
    if (this != &o) {
        produtos_ = o.produtos_; lotes_ = o.lotes_; vendas_ = o.vendas_;
        proximoIdLote_ = o.proximoIdLote_; proximoIdVenda_ = o.proximoIdVenda_;
    }
    return *this;
}
BancoImpl::~BancoImpl() {}

Produto* BancoImpl::buscarProduto(const std::string& codigo) {
    for (size_t i = 0; i < produtos_.size(); ++i)
        if (produtos_[i].codigo() == codigo) return &produtos_[i];
    return nullptr;
}
const Produto* BancoImpl::buscarProduto(const std::string& codigo) const {
    for (size_t i = 0; i < produtos_.size(); ++i)
        if (produtos_[i].codigo() == codigo) return &produtos_[i];
    return nullptr;
}
void BancoImpl::adicionarProduto(const Produto& p) {
    //guarda uma copia concreta, pelos getters da interface 
    ProdutoImpl copia(p.codigo(), p.nome(), p.categoria(), p.custo(), p.estoqueMinimo());
    if (p.temPreco()) {
        copia.setPreco(p.preco());
    }
    produtos_.push_back(copia); 
}
int BancoImpl::quantidadeProdutos() const {
    return (int)produtos_.size();
}
const Produto& BancoImpl::produto(int i) const {
    return produtos_[i];
}

const LoteEstoque& BancoImpl::adicionarLote(int idUnidade, const std::string& codigoProduto,
                                 int quantidade, const Data& dataEntrada,
                                 const Data& validade) {
    LoteEstoqueImpl l(proximoIdLote_++, idUnidade, codigoProduto, quantidade,
                  dataEntrada, validade);
    lotes_.push_back(l);
    return lotes_.back(); //lote guardado no banco, nao a copia local 
}
int BancoImpl::quantidadeLotes() const {
    return (int)lotes_.size();
}
LoteEstoque& BancoImpl::lote(int i) {
    return lotes_[i];
}
const LoteEstoque& BancoImpl::lote(int i) const {
    return lotes_[i];
}
const LoteEstoque* BancoImpl::buscarLote(int id) const {
    for (size_t i = 0; i < lotes_.size(); ++i)
        if (lotes_[i].id() == id) return &lotes_[i];
    return nullptr;
}

int BancoImpl::saldoValido(int idUnidade, const std::string& codigoProduto,
                       const Data& hoje) const {
    int total = 0;
    for (size_t i = 0; i < lotes_.size(); ++i) {
        const LoteEstoque& l = lotes_[i];
        if (l.idUnidade() == idUnidade && l.codigoProduto() == codigoProduto
            && !l.vencido(hoje))
            total += l.saldo();
    }
    return total;
}

const Venda& BancoImpl::adicionarVenda(int idUnidade, const std::string& codigoProduto,
                            int quantidade, const Dinheiro& valorTotal,
                            const Data& data, int idUsuario) {
    VendaImpl v(proximoIdVenda_++, idUnidade, codigoProduto, quantidade,
            valorTotal, data, idUsuario);
    vendas_.push_back(v);
    return vendas_.back();
}
int BancoImpl::quantidadeVendas() const{
    return (int)vendas_.size();
}
const Venda& BancoImpl::venda(int i) const {
    return vendas_[i];
}