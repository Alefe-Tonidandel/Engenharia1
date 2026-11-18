#ifndef DINHEIRO_H
#define DINHEIRO_H

#include <cstdint>
#include <iostream>

// Valor em centavos (inteiro): sem erro de arredondamento do double.
class Dinheiro {
public:
    Dinheiro();                                   // R$ 0,00
    Dinheiro(const Dinheiro& o);
    Dinheiro& operator=(const Dinheiro& o);
    ~Dinheiro();

    static Dinheiro reais(double r);              // reais(11.20) -> 1120 centavos
    int64_t centavos() const;
    Dinheiro operator*(int qtd) const;
    bool operator<(const Dinheiro& o) const;
    bool operator==(const Dinheiro& o) const;

private:
    explicit Dinheiro(int64_t centavos);
    int64_t centavos_;
};

std::ostream& operator<<(std::ostream& os, const Dinheiro& d);   // R$ 22,40

#endif
