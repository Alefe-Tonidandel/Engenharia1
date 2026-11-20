#include "venda.h"

Venda::Venda()
    : id_(0), idUnidade_(0), codigoProduto_(), quantidade_(0),
      valorTotal_(), data_(), idUsuario_(0) {}
Venda::Venda(int id, int idUnidade, const std::string& codigoProduto,
             int quantidade, const Dinheiro& valorTotal, const Data& data,
             int idUsuario)
    : id_(id), idUnidade_(idUnidade), codigoProduto_(codigoProduto),
      quantidade_(quantidade), valorTotal_(valorTotal), data_(data),
      idUsuario_(idUsuario) {}
Venda::Venda(const Venda& o)
    : id_(o.id_), idUnidade_(o.idUnidade_), codigoProduto_(o.codigoProduto_),
      quantidade_(o.quantidade_), valorTotal_(o.valorTotal_), data_(o.data_),
      idUsuario_(o.idUsuario_) {}
Venda& Venda::operator=(const Venda& o) {
    if (this != &o) {
        id_ = o.id_; idUnidade_ = o.idUnidade_; codigoProduto_ = o.codigoProduto_;
        quantidade_ = o.quantidade_; valorTotal_ = o.valorTotal_;
        data_ = o.data_; idUsuario_ = o.idUsuario_;
    }
    return *this;
}
Venda::~Venda() {}

int Venda::id() const { return id_; }
int Venda::idUnidade() const { return idUnidade_; }
const std::string& Venda::codigoProduto() const { return codigoProduto_; }
int Venda::quantidade() const { return quantidade_; }
const Dinheiro& Venda::valorTotal() const { return valorTotal_; }
const Data& Venda::data() const { return data_; }
int Venda::idUsuario() const { return idUsuario_; }
