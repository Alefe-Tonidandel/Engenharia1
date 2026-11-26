#include "venda_impl.h"

VendaImpl::VendaImpl()
    : id_(0), idUnidade_(0), codigoProduto_(), quantidade_(0),
      valorTotal_(), data_(), idUsuario_(0) {}
VendaImpl::VendaImpl(int id, int idUnidade, const std::string& codigoProduto,
             int quantidade, const Dinheiro& valorTotal, const Data& data,
             int idUsuario)
    : id_(id), idUnidade_(idUnidade), codigoProduto_(codigoProduto),
      quantidade_(quantidade), valorTotal_(valorTotal), data_(data),
      idUsuario_(idUsuario) {}
VendaImpl::VendaImpl(const VendaImpl& o)
    : Venda(), id_(o.id_), idUnidade_(o.idUnidade_), codigoProduto_(o.codigoProduto_),
      quantidade_(o.quantidade_), valorTotal_(o.valorTotal_), data_(o.data_),
      idUsuario_(o.idUsuario_) {}
VendaImpl& VendaImpl::operator=(const VendaImpl& o) {
    if (this != &o) {
        id_ = o.id_; idUnidade_ = o.idUnidade_; codigoProduto_ = o.codigoProduto_;
        quantidade_ = o.quantidade_; valorTotal_ = o.valorTotal_;
        data_ = o.data_; idUsuario_ = o.idUsuario_;
    }
    return *this;
}
VendaImpl::~VendaImpl() {}

int VendaImpl::id() const { return id_; }
int VendaImpl::idUnidade() const { return idUnidade_; }
const std::string& VendaImpl::codigoProduto() const { return codigoProduto_; }
int VendaImpl::quantidade() const { return quantidade_; }
const Dinheiro& VendaImpl::valorTotal() const { return valorTotal_; }
const Data& VendaImpl::data() const { return data_; }
int VendaImpl::idUsuario() const { return idUsuario_; }