#ifndef SERVICO_ESTOQUE_H
#define SERVICO_ESTOQUE_H

#include <string>
#include "tipos.h"
#include "usuario.h"
#include "banco.h"

// Entradas e vendas da unidade da sessao.
class ServicoEstoque {
public:
    ServicoEstoque();
    ServicoEstoque(const Sessao& sessao, Banco& banco);
    ServicoEstoque(const ServicoEstoque& o);
    ServicoEstoque& operator=(const ServicoEstoque& o);
    ~ServicoEstoque();

    // Repositor ou Gerente: cria um lote na unidade da sessao
    Resultado<LoteEstoque> registrarEntrada(const std::string& codigo,
                                            int quantidade,
                                            const Data& validade);

    // Operador ou Gerente: vende pelo lote que vence primeiro (FEFO),
    // nunca de lote vencido
    Resultado<Venda> registrarVenda(const std::string& codigo, int quantidade);

private:
    const Sessao* sessao_;
    Banco*        banco_;
};

#endif
