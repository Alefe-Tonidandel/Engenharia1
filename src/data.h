#ifndef DATA_H
#define DATA_H

#include <iostream>

class Data {
public:
    Data();                                  
    Data(int ano, int mes, int dia);
    Data(const Data& o);                     // construtor de copia
    Data& operator=(const Data& o);          // atribuicao
    ~Data();                                 // destrutor

    int ano() const;
    int mes() const;
    int dia() const;
    bool operator<(const Data& o) const;
    bool operator==(const Data& o) const;

private:
    int ano_, mes_, dia_;
};

std::ostream& operator<<(std::ostream& os, const Data& d);   // dd/mm/aaaa

//Permite fixar a data nos testes.
class Relogio {
public:
    static Data hoje();
    static void fixar(const Data& d);
private:
    Relogio();
};

#endif
