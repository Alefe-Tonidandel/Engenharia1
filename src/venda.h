/**
 * @file venda.h
 * @brief Interface Venda
 */
#ifndef VENDA_H
#define VENDA_H

#include <string>
#include "data.h"
#include "dinheiro.h"

/**
 * @brief Registro de uma venda 
 * 
 */
class Venda {
public:
    virtual ~Venda(){} 
    virtual int id() const = 0;
    virtual int idUnidade() const = 0;
    virtual const std::string& codigoProduto() const = 0;
    virtual int quantidade() const = 0;
    virtual const Dinheiro& valorTotal() const = 0;
    virtual const Data& data() const = 0;
    virtual int idUsuario() const = 0;
};

#endif
