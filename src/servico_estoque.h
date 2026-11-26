/**
 * @file servico_estoque.h
 * @brief Interface ServicoEstoque
 */
#ifndef SERVICO_ESTOQUE_H
#define SERVICO_ESTOQUE_H

#include <string>
#include <vector>
#include "tipos.h"
#include "item_estoque.h"
#include "lote.h"
#include "venda.h"

/**
 * @brief Servico de estoque
 * @details Registra entradas de lotes e vendas, sempre na unidade do usuario logado e consulta o estoque
 * 
 */
class ServicoEstoque {
public:
    virtual ~ServicoEstoque(){}
    virtual Resultado<const LoteEstoque*> registrarEntrada(const std::string& codigo, int quantidade, const Data& validade) = 0;
    virtual Resultado<const Venda*> registrarVenda(const std::string& codigo, int quantidade) = 0;
    virtual Resultado<std::vector<ItemEstoque> > consultarEstoque(const FiltroEstoque& filtro) = 0;
};

#endif
