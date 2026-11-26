#include "lote_impl.h"

LoteEstoqueImpl::LoteEstoqueImpl()
    : id_(0), idUnidade_(0), codigoProduto_(), quantidadeInicial_(0),
      saldo_(0), dataEntrada_(), validade_() {}
LoteEstoqueImpl::LoteEstoqueImpl(int id, int idUnidade, const std::string& codigoProduto, int quantidade, const Data& dataEntrada, const Data& validade)
    : id_(id), idUnidade_(idUnidade), codigoProduto_(codigoProduto),
      quantidadeInicial_(quantidade), saldo_(quantidade),
      dataEntrada_(dataEntrada), validade_(validade) {}
LoteEstoqueImpl::LoteEstoqueImpl(const LoteEstoqueImpl& o)
    : LoteEstoque(), id_(o.id_), idUnidade_(o.idUnidade_), codigoProduto_(o.codigoProduto_),
      quantidadeInicial_(o.quantidadeInicial_), saldo_(o.saldo_),
      dataEntrada_(o.dataEntrada_), validade_(o.validade_) {}
LoteEstoqueImpl& LoteEstoqueImpl::operator=(const LoteEstoqueImpl& o) {
    if (this != &o) {
        id_ = o.id_; idUnidade_ = o.idUnidade_; codigoProduto_ = o.codigoProduto_;
        quantidadeInicial_ = o.quantidadeInicial_; saldo_ = o.saldo_;
        dataEntrada_ = o.dataEntrada_; validade_ = o.validade_;
    }
    return *this;
}
LoteEstoqueImpl::~LoteEstoqueImpl() {}

int LoteEstoqueImpl::id() const { return id_; }
int LoteEstoqueImpl::idUnidade() const { return idUnidade_; }
const std::string& LoteEstoqueImpl::codigoProduto() const { return codigoProduto_; }
int LoteEstoqueImpl::quantidadeInicial() const { return quantidadeInicial_; }
int LoteEstoqueImpl::saldo() const { return saldo_; }
const Data& LoteEstoqueImpl::dataEntrada() const { return dataEntrada_; }
const Data& LoteEstoqueImpl::validade() const { return validade_; }

bool LoteEstoqueImpl::vencido(const Data& hoje) const { return validade_ < hoje; }
void LoteEstoqueImpl::baixar(int quantidade) { saldo_ -= quantidade; }

