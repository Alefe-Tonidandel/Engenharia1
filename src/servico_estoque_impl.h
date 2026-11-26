/**
 * @file servico_estoque_impl.h
 * @brief Declaracao de ServicoEstoqueImpl
 */
#ifndef SERVICO_ESTOQUE_IMPL_H
#define SERVICO_ESTOQUE_IMPL_H

#include "sessao.h"
#include "banco.h"
#include "servico_estoque.h"


/**
 * @brief Implementacao concreta de ServicoEstoque
 * 
 */
class ServicoEstoqueImpl : public ServicoEstoque {
public:
    ServicoEstoqueImpl();
    ServicoEstoqueImpl(const Sessao& sessao, Banco& banco);
    ServicoEstoqueImpl(const ServicoEstoqueImpl& o);
    ServicoEstoqueImpl& operator=(const ServicoEstoqueImpl& o);
    ~ServicoEstoqueImpl();


    Resultado<const LoteEstoque*> registrarEntrada(const std::string& codigo, int quantidade, const Data& validade) override;
    Resultado<const Venda*> registrarVenda(const std::string& codigo, int quantidade) override;
    Resultado<std::vector<ItemEstoque> > consultarEstoque(const FiltroEstoque& filtro) override;

private:
    const Sessao* sessao_;
    Banco*        banco_;
};

#endif