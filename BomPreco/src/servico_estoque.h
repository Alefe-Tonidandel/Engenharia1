/**
 * @file servico_estoque.h
 * @brief Declaracao do ServicoEstoque - entrada de lotes e vendas
 */
#ifndef SERVICO_ESTOQUE_H
#define SERVICO_ESTOQUE_H

#include <string>
#include "tipos.h"
#include "usuario.h"
#include "banco.h"

// Entradas e vendas da unidade da sessao.
/**
 * @brief Servico de estoque 
 * @details Registra entrada de lotes ou registra venda de produtos
 * 
 */
class ServicoEstoque {
public:
    ServicoEstoque();
    /**
     * @brief Cria um servico ligado a uma sessao e a um banco
     * 
     * @param sessao Usuario logado
     * @param banco Banco onde os lotes e as vendas sao gravados
     */
    ServicoEstoque(const Sessao& sessao, Banco& banco);
    ServicoEstoque(const ServicoEstoque& o);
    ServicoEstoque& operator=(const ServicoEstoque& o);
    ~ServicoEstoque();

    // Repositor ou Gerente: cria um lote na unidade da sessao
    /**
     * @brief Registrar entrada, apenas por repositor ou gerente
     * 
     * @param codigo Codigo do produto
     * @param quantidade Quantidade que esta entrando
     * @param validade Validade do produto
     * @return Retorna o lote criado ou erro
     */
    Resultado<LoteEstoque> registrarEntrada(const std::string& codigo,
                                            int quantidade,
                                            const Data& validade);

    // Operador ou Gerente: vende pelo lote que vence primeiro (FEFO),
    // nunca de lote vencido
    /**
     * @brief Registrar venda de produtos, apenas operador ou gerente
     * @details A venda é feita pela lógica de FEFO: sai do lote que vence primeiro, nunca lote vencido
     * @param codigo Codigo do produto
     * @param quantidade Quantidade vendida
     * @return Retorna a venda registrada ou erro 
     */
    Resultado<Venda> registrarVenda(const std::string& codigo, int quantidade);

private:
    const Sessao* sessao_;
    Banco*        banco_;
};

#endif
