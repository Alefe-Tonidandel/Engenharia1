#include "data.h"
#include <ctime>
#include <iomanip>

Data::Data() : ano_(1970), mes_(1), dia_(1) {}
Data::Data(int ano, int mes, int dia) : ano_(ano), mes_(mes), dia_(dia) {}
Data::Data(const Data& o) : ano_(o.ano_), mes_(o.mes_), dia_(o.dia_) {}
Data& Data::operator=(const Data& o) {
    if (this != &o) { ano_ = o.ano_; mes_ = o.mes_; dia_ = o.dia_; }
    return *this;
}
Data::~Data() {}

int Data::ano() const { return ano_; }
int Data::mes() const { return mes_; }
int Data::dia() const { return dia_; }

bool Data::operator<(const Data& o) const {
    if (ano_ != o.ano_) return ano_ < o.ano_;
    if (mes_ != o.mes_) return mes_ < o.mes_;
    return dia_ < o.dia_;
}
bool Data::operator==(const Data& o) const {
    return ano_ == o.ano_ && mes_ == o.mes_ && dia_ == o.dia_;
}

std::ostream& operator<<(std::ostream& os, const Data& d) {
    char antes = os.fill('0');
    os << std::setw(2) << d.dia() << '/' << std::setw(2) << d.mes()
       << '/' << d.ano();
    os.fill(antes);
    return os;
}

// ---- Relogio ----
static bool fixada_ = false;
static Data dataFixa_;

Data Relogio::hoje() {
    if (fixada_) return dataFixa_;
    std::time_t t = std::time(nullptr);
    std::tm* l = std::localtime(&t);
    return Data(l->tm_year + 1900, l->tm_mon + 1, l->tm_mday);
}
void Relogio::fixar(const Data& d) { dataFixa_ = d; fixada_ = true; }
