/**
 * @file data.h
 * @brief Declaração das classes Data e Relogio
 */
#ifndef DATA_H
#define DATA_H

#include <string>
#include <iostream>
/**
 * @brief Data do calendario
 * 
 */
class Data {
public:
    Data();                              // 01/01/1970
    /**
     * @brief Cria uma data
     * 
     * @param ano Ano(ex.: 2026)
     * @param mes Mes(1 a 12)
     * @param dia Dia do mes
     */
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

/**
 * @brief Data de hoje 
 * 
 * 
 */
//permite fixar as datas nos testes
 class Relogio {
public:
    static Data hoje();
    /**
     * @brief Fixar a data retornada por hoje()
     * 
     * @param d Data que passa a ser considerada "hoje"
     */
    static void fixar(const Data& d);
private:
    Relogio();
};

#endif
