#include "lote.h"

LoteEstoque::LoteEstoque()
    : id_(0), idUnidade_(0), codigoProduto_(), quantidadeInicial_(0),
      saldo_(0), dataEntrada_(), validade_() {}
LoteEstoque::LoteEstoque(int id, int idUnidade, const std::string& codigoProduto,
                         int quantidade, const Data& dataEntrada,
                         const Data& validade)
    : id_(id), idUnidade_(idUnidade), codigoProduto_(codigoProduto),
      quantidadeInicial_(quantidade), saldo_(quantidade),
      dataEntrada_(dataEntrada), validade_(validade) {}
LoteEstoque::LoteEstoque(const LoteEstoque& o)
    : id_(o.id_), idUnidade_(o.idUnidade_), codigoProduto_(o.codigoProduto_),
      quantidadeInicial_(o.quantidadeInicial_), saldo_(o.saldo_),
      dataEntrada_(o.dataEntrada_), validade_(o.validade_) {}
LoteEstoque& LoteEstoque::operator=(const LoteEstoque& o) {
    if (this != &o) {
        id_ = o.id_; idUnidade_ = o.idUnidade_; codigoProduto_ = o.codigoProduto_;
        quantidadeInicial_ = o.quantidadeInicial_; saldo_ = o.saldo_;
        dataEntrada_ = o.dataEntrada_; validade_ = o.validade_;
    }
    return *this;
}
LoteEstoque::~LoteEstoque() {}

int LoteEstoque::id() const { return id_; }
int LoteEstoque::idUnidade() const { return idUnidade_; }
const std::string& LoteEstoque::codigoProduto() const { return codigoProduto_; }
int LoteEstoque::quantidadeInicial() const { return quantidadeInicial_; }
int LoteEstoque::saldo() const { return saldo_; }
const Data& LoteEstoque::dataEntrada() const { return dataEntrada_; }
const Data& LoteEstoque::validade() const { return validade_; }

bool LoteEstoque::vencido(const Data& hoje) const { return validade_ < hoje; }
void LoteEstoque::baixar(int quantidade) { saldo_ -= quantidade; }
