/**
 * @file unit_ServicoEstoqueImpl.cpp
 * @brief Testes unitarios da classe ServicoEstoqueImpl
 *
 * Usa os cenarios 4.3 (entrada), 4.4 (venda) e 4.5 (consulta) da Sprint 2.
 * Usuarios: Joana Reis (Repositor, un. 1), Pedro Alves (Operador, un. 1) e
 * Rafael Lima (Gestor da Rede).
 * Obs.: o ponteiro devolvido no Resultado aponta para dentro do banco; por isso
 * os valores sao conferidos logo depois de cada chamada.
 */
#include <cassert>
#include "unit_ServicoEstoqueImpl.h"
#include "../../src/servico_estoque_impl.h"
#include "../../src/banco_impl.h"
#include "../../src/sessao_impl.h"
#include "../../src/usuario_impl.h"

// Catalogo da Tabela 3 ja com os precos
static void montarCatalogo(BancoImpl& banco) {
    ProdutoImpl tomate("BP-1265", "Tomate italiano (kg)", "Hortifruti", Dinheiro::reais(8.40), 20);
    tomate.setPreco(Dinheiro::reais(11.20));
    ProdutoImpl arroz("BP-0501", "Arroz branco 5 kg", "Mercearia", Dinheiro::reais(22.00), 40);
    arroz.setPreco(Dinheiro::reais(26.90));
    ProdutoImpl leite("BP-0720", "Leite integral 1 L", "Laticinios", Dinheiro::reais(3.60), 60);
    leite.setPreco(Dinheiro::reais(4.49));
    ProdutoImpl feijao("BP-0999", "Feijao preto 1 kg", "Mercearia", Dinheiro::reais(6.80), 30);
    banco.adicionarProduto(tomate);
    banco.adicionarProduto(arroz);
    banco.adicionarProduto(leite);
    banco.adicionarProduto(feijao);                   // sem preco
}

// Lotes da Tabela 4 (entrada em 26/10/2026, unidade 1)
static void montarLotes(BancoImpl& banco) {
    banco.adicionarLote(1, "BP-1265", 30, Data(2026, 10, 26), Data(2026, 10, 30));   // lote 1
    banco.adicionarLote(1, "BP-1265", 50, Data(2026, 10, 26), Data(2026, 11, 5));    // lote 2
    banco.adicionarLote(1, "BP-0501", 100, Data(2026, 10, 26), Data(2027, 3, 1));    // lote 3
    banco.adicionarLote(1, "BP-0720", 40, Data(2026, 10, 26), Data(2026, 12, 15));   // lote 4
}

void unit_ServicoEstoqueImpl_construtor(void){
    ServicoEstoqueImpl semSessao;                     // construtor padrao: recusa tudo
    assert(semSessao.registrarVenda("BP-1265", 2).erro == Erro::AcessoNegado);

    BancoImpl banco;
    montarCatalogo(banco);
    Relogio::fixar(Data(2026, 10, 26));
    SessaoImpl repo(UsuarioImpl(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoqueImpl estoque(repo, banco);          // ligado a sessao e ao banco
    assert(estoque.registrarEntrada("BP-1265", 30, Data(2026, 10, 30)).ok());
    assert(banco.quantidadeLotes() == 1);
}

void unit_ServicoEstoqueImpl_copyConstrutor(void){
    BancoImpl banco;
    montarCatalogo(banco);
    Relogio::fixar(Data(2026, 10, 26));
    SessaoImpl repo(UsuarioImpl(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoqueImpl original(repo, banco);
    ServicoEstoqueImpl copia(original);               // mesma sessao e mesmo banco
    assert(copia.registrarEntrada("BP-1265", 30, Data(2026, 10, 30)).ok());
    assert(banco.quantidadeLotes() == 1);
}

void unit_ServicoEstoqueImpl_operatorAtribuicao(void){
    BancoImpl banco;
    montarCatalogo(banco);
    Relogio::fixar(Data(2026, 10, 26));
    SessaoImpl repo(UsuarioImpl(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoqueImpl original(repo, banco);
    ServicoEstoqueImpl s;
    s = original;
    assert(s.registrarEntrada("BP-1265", 30, Data(2026, 10, 30)).ok());
    assert(banco.quantidadeLotes() == 1);
}

void unit_ServicoEstoqueImpl_destrutor(void){
    BancoImpl banco;
    montarCatalogo(banco);
    SessaoImpl repo(UsuarioImpl(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoqueImpl* s = new ServicoEstoqueImpl(repo, banco);
    delete s;                                         // nao apaga a sessao nem o banco
    assert(banco.quantidadeProdutos() == 4);
}

void unit_ServicoEstoqueImpl_registrarEntrada(void){
    BancoImpl banco;
    montarCatalogo(banco);
    Relogio::fixar(Data(2026, 10, 26));
    SessaoImpl repo(UsuarioImpl(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoqueImpl estoque(repo, banco);

    // ok: lote 1, saldo 30, na unidade da sessao
    Resultado<const LoteEstoque*> r = estoque.registrarEntrada("BP-1265", 30, Data(2026, 10, 30));
    assert(r.ok());
    assert(r.valor->id() == 1 && r.valor->saldo() == 30 && r.valor->idUnidade() == 1);
    assert(r.valor->dataEntrada() == Data(2026, 10, 26));

    // ok: outro lote do mesmo produto -> BP-1265 com 80 em 2 lotes
    assert(estoque.registrarEntrada("BP-1265", 50, Data(2026, 11, 5)).ok());
    assert(banco.saldoValido(1, "BP-1265", Data(2026, 10, 26)) == 80);

    // erros: nenhum lote novo e criado
    assert(estoque.registrarEntrada("BP-1265", 10, Data(2026, 10, 20)).erro == Erro::ValidadeVencida);
    assert(estoque.registrarEntrada("BP-1265", 0, Data(2026, 11, 5)).erro == Erro::QuantidadeInvalida);
    assert(estoque.registrarEntrada("BP-0000", 10, Data(2026, 11, 5)).erro == Erro::NaoEncontrado);

    SessaoImpl op(UsuarioImpl(31, "Pedro Alves", Perfil::OperadorCaixa, 1));
    ServicoEstoqueImpl caixa(op, banco);
    assert(caixa.registrarEntrada("BP-1265", 5, Data(2026, 12, 1)).erro == Erro::AcessoNegado);

    assert(banco.quantidadeLotes() == 2);
}

void unit_ServicoEstoqueImpl_registrarVenda(void){
    BancoImpl banco;
    montarCatalogo(banco);
    montarLotes(banco);
    SessaoImpl op(UsuarioImpl(31, "Pedro Alves", Perfil::OperadorCaixa, 1));
    ServicoEstoqueImpl caixa(op, banco);

    // 28/10: vende 2 e sai do lote 1, que vence primeiro
    Relogio::fixar(Data(2026, 10, 28));
    Resultado<const Venda*> v = caixa.registrarVenda("BP-1265", 2);
    assert(v.ok() && v.valor->valorTotal() == Dinheiro::reais(22.40));
    assert(banco.lote(0).saldo() == 28 && banco.lote(1).saldo() == 50);

    // 31/10: o lote 1 venceu, entao sai do lote 2
    Relogio::fixar(Data(2026, 10, 31));
    v = caixa.registrarVenda("BP-1265", 2);
    assert(v.ok() && v.valor->valorTotal() == Dinheiro::reais(22.40));
    assert(banco.lote(0).saldo() == 28 && banco.lote(1).saldo() == 48);

    // 31/10: venda de 40 -> R$ 448,00, lote 2 fica com 8
    v = caixa.registrarVenda("BP-1265", 40);
    assert(v.ok() && v.valor->valorTotal() == Dinheiro::reais(448.00));
    assert(banco.lote(1).saldo() == 8);

    // erros: nenhuma venda e gravada
    int vendas = banco.quantidadeVendas();
    assert(caixa.registrarVenda("BP-1265", 60).erro == Erro::EstoqueInsuficiente);
    assert(caixa.registrarVenda("BP-0999", 1).erro == Erro::ProdutoSemPreco);
    assert(caixa.registrarVenda("BP-0000", 1).erro == Erro::NaoEncontrado);
    assert(caixa.registrarVenda("BP-1265", 0).erro == Erro::QuantidadeInvalida);

    SessaoImpl repo(UsuarioImpl(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoqueImpl estoque(repo, banco);
    assert(estoque.registrarVenda("BP-1265", 1).erro == Erro::AcessoNegado);

    assert(banco.quantidadeVendas() == vendas);
    assert(banco.lote(1).saldo() == 8);               // saldos nao mudaram
}

void unit_ServicoEstoqueImpl_consultarEstoque(void){
    BancoImpl banco;
    montarCatalogo(banco);
    montarLotes(banco);
    SessaoImpl repo(UsuarioImpl(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoqueImpl estoque(repo, banco);

    // 26/10, Hortifruti: BP-1265 com 80, vencida 0, validade 30/10
    Relogio::fixar(Data(2026, 10, 26));
    FiltroEstoque horti;
    horti.categoria = "Hortifruti";
    Resultado<std::vector<ItemEstoque> > c = estoque.consultarEstoque(horti);
    assert(c.ok() && c.valor.size() == 1);
    assert(c.valor[0].codigoProduto() == "BP-1265" && c.valor[0].quantidade() == 80);
    assert(c.valor[0].quantidadeVencida() == 0 && !c.valor[0].abaixoDoMinimo());
    assert(c.valor[0].validadeMaisProxima() == Data(2026, 10, 30));

    // 26/10, Laticinios: BP-0720 com 40, minimo 60 -> abaixo do minimo
    FiltroEstoque lat;
    lat.categoria = "Laticinios";
    c = estoque.consultarEstoque(lat);
    assert(c.ok() && c.valor[0].codigoProduto() == "BP-0720");
    assert(c.valor[0].quantidade() == 40 && c.valor[0].abaixoDoMinimo());

    // 31/10, Hortifruti: 50 validos e 30 vencidos
    Relogio::fixar(Data(2026, 10, 31));
    c = estoque.consultarEstoque(horti);
    assert(c.valor[0].quantidade() == 50 && c.valor[0].quantidadeVencida() == 30);

    // Padaria (vazia): ok, lista vazia
    FiltroEstoque padaria;
    padaria.categoria = "Padaria";
    c = estoque.consultarEstoque(padaria);
    assert(c.ok() && c.valor.empty());

    // Repositor da un. 1 tenta ver a unidade 2
    FiltroEstoque un2;
    un2.idUnidade = 2;
    assert(estoque.consultarEstoque(un2).erro == Erro::AcessoNegado);

    // Gestor da Rede: precisa informar a unidade
    SessaoImpl gestor(UsuarioImpl(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoEstoqueImpl rede(gestor, banco);
    FiltroEstoque semUnidade;
    assert(rede.consultarEstoque(semUnidade).erro == Erro::UnidadeNaoInformada);
    FiltroEstoque un1;
    un1.idUnidade = 1;
    assert(rede.consultarEstoque(un1).ok());

    // Operador de Caixa nao consulta estoque
    SessaoImpl op(UsuarioImpl(31, "Pedro Alves", Perfil::OperadorCaixa, 1));
    ServicoEstoqueImpl caixa(op, banco);
    assert(caixa.consultarEstoque(semUnidade).erro == Erro::AcessoNegado);
}

void run_unit_tests_ServicoEstoqueImpl(void){
    unit_ServicoEstoqueImpl_construtor();
    unit_ServicoEstoqueImpl_copyConstrutor();
    unit_ServicoEstoqueImpl_operatorAtribuicao();
    unit_ServicoEstoqueImpl_destrutor();
    unit_ServicoEstoqueImpl_registrarEntrada();
    unit_ServicoEstoqueImpl_registrarVenda();
    unit_ServicoEstoqueImpl_consultarEstoque();
}
