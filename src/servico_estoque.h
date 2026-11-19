#ifndef SERVICO_ESTOQUE_H
#define SERVICO_ESTOQUE_H

#include <string>
#include <vector>
#include "tipos.h"
#include "usuario.h"
#include "banco.h"
#include "item_estoque.h"

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

    // Operador ou Gerente: vende pelo lote que vence primeiro,
    // nunca de lote vencido
    Resultado<Venda> registrarVenda(const std::string& codigo, int quantidade);
    Resultado<std::vector<ItemEstoque> > consultarEstoque(const FiltroEstoque& filtro);

private:
    const Sessao* sessao_;
    Banco*        banco_;
};

#endif
