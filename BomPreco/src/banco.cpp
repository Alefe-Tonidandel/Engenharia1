#include "banco.h"

Banco::Banco() : produtos_(), lotes_(), vendas_(),
                 proximoIdLote_(1), proximoIdVenda_(1) {}
Banco::Banco(const Banco& o)
    : produtos_(o.produtos_), lotes_(o.lotes_), vendas_(o.vendas_),
      proximoIdLote_(o.proximoIdLote_), proximoIdVenda_(o.proximoIdVenda_) {}
Banco& Banco::operator=(const Banco& o) {
    if (this != &o) {
        produtos_ = o.produtos_; lotes_ = o.lotes_; vendas_ = o.vendas_;
        proximoIdLote_ = o.proximoIdLote_; proximoIdVenda_ = o.proximoIdVenda_;
    }
    return *this;
}
Banco::~Banco() {}

Produto* Banco::buscarProduto(const std::string& codigo) {
    for (size_t i = 0; i < produtos_.size(); ++i)
        if (produtos_[i].codigo() == codigo) return &produtos_[i];
    return nullptr;
}
const Produto* Banco::buscarProduto(const std::string& codigo) const {
    for (size_t i = 0; i < produtos_.size(); ++i)
        if (produtos_[i].codigo() == codigo) return &produtos_[i];
    return nullptr;
}
void Banco::adicionarProduto(const Produto& p) { produtos_.push_back(p); }

LoteEstoque Banco::adicionarLote(int idUnidade, const std::string& codigoProduto,
                                 int quantidade, const Data& dataEntrada,
                                 const Data& validade) {
    LoteEstoque l(proximoIdLote_++, idUnidade, codigoProduto, quantidade,
                  dataEntrada, validade);
    lotes_.push_back(l);
    return l;
}
std::vector<LoteEstoque>& Banco::lotes() { return lotes_; }
const std::vector<LoteEstoque>& Banco::lotes() const { return lotes_; }
const LoteEstoque* Banco::buscarLote(int id) const {
    for (size_t i = 0; i < lotes_.size(); ++i)
        if (lotes_[i].id() == id) return &lotes_[i];
    return nullptr;
}

int Banco::saldoValido(int idUnidade, const std::string& codigoProduto,
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

Venda Banco::adicionarVenda(int idUnidade, const std::string& codigoProduto,
                            int quantidade, const Dinheiro& valorTotal,
                            const Data& data, int idUsuario) {
    Venda v(proximoIdVenda_++, idUnidade, codigoProduto, quantidade,
            valorTotal, data, idUsuario);
    vendas_.push_back(v);
    return v;
}
const std::vector<Venda>& Banco::vendas() const { return vendas_; }
