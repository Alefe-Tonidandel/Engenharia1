#include "dinheiro.h"
#include <cmath>
#include <cstdlib>

Dinheiro::Dinheiro() : centavos_(0) {}
Dinheiro::Dinheiro(int64_t c) : centavos_(c) {}
Dinheiro::Dinheiro(const Dinheiro& o) : centavos_(o.centavos_) {}
Dinheiro& Dinheiro::operator=(const Dinheiro& o) {
    if (this != &o) centavos_ = o.centavos_;
    return *this;
}
Dinheiro::~Dinheiro() {}

Dinheiro Dinheiro::reais(double r) {
    return Dinheiro(static_cast<int64_t>(std::llround(r * 100.0)));
}
int64_t Dinheiro::centavos() const { return centavos_; }
Dinheiro Dinheiro::operator*(int qtd) const { return Dinheiro(centavos_ * qtd); }
bool Dinheiro::operator<(const Dinheiro& o) const { return centavos_ < o.centavos_; }
bool Dinheiro::operator==(const Dinheiro& o) const { return centavos_ == o.centavos_; }

std::ostream& operator<<(std::ostream& os, const Dinheiro& d) {
    int64_t c = d.centavos();
    if (c < 0) { os << "-"; c = -c; }
    os << "R$ " << c / 100 << ',' << (c % 100 < 10 ? "0" : "") << c % 100;
    return os;
}
