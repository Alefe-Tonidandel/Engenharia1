#include <cassert>
#include <iostream>
#include "funcional_tests.h"
#include "../../src/banco.h"
#include "../../src/servico_cadastros.h"
#include "../../src/servico_estoque.h"

// ---- apoio: monta o catalogo da Tabela 3 do Sprint 2 ----
static void montarCatalogo(Banco& banco) {
    Sessao gestor(Usuario(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoCadastros cad(gestor, banco);
    DadosProduto d[] = {
        {"BP-1265", "Tomate italiano (kg)", "Hortifruti", Dinheiro::reais(8.40),  20},
        {"BP-0501", "Arroz branco 5 kg",    "Mercearia",  Dinheiro::reais(22.00), 40},
        {"BP-0720", "Leite integral 1 L",   "Laticinios", Dinheiro::reais(3.60),  60},
        {"BP-0999", "Feijao preto 1 kg",    "Mercearia",  Dinheiro::reais(6.80),  30}};
    for (int i = 0; i < 4; ++i) cad.cadastrarProduto(d[i]);
    cad.definirPrecoPadrao("BP-1265", Dinheiro::reais(11.20));
    cad.definirPrecoPadrao("BP-0501", Dinheiro::reais(26.90));
    cad.definirPrecoPadrao("BP-0720", Dinheiro::reais(4.49));   // BP-0999 fica sem preco
}

// ---- apoio: lotes da Tabela 4 (unidade 1, entrada em 26/10/2026) ----
static void montarLotes(Banco& banco) {
    Relogio::fixar(Data(2026, 10, 26));
    Sessao repo(Usuario(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoque estoque(repo, banco);
    estoque.registrarEntrada("BP-1265", 30, Data(2026, 10, 30));   // lote 1
    estoque.registrarEntrada("BP-1265", 50, Data(2026, 11, 5));    // lote 2
    estoque.registrarEntrada("BP-0501", 100, Data(2027, 3, 1));    // lote 3
    estoque.registrarEntrada("BP-0720", 40, Data(2026, 12, 15));   // lote 4
}

// ============ Funcional 1: Gestor da Rede ============
void cadastroFuncionalTest() {
    Banco banco;
    Sessao gestor(Usuario(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoCadastros cad(gestor, banco);

    // cadastrar: produto entra sem preco
    DadosProduto tomate = {"BP-1265", "Tomate italiano (kg)", "Hortifruti",
                           Dinheiro::reais(8.40), 20};
    Resultado<Produto> r = cad.cadastrarProduto(tomate);
    assert(r.ok());
    assert(!r.valor.temPreco());
    assert(banco.buscarProduto("BP-1265") != nullptr);

    // cadastros recusados
    assert(cad.cadastrarProduto(tomate).erro == Erro::Duplicado);
    DadosProduto semNome = {"BP-7", "", "Mercearia", Dinheiro::reais(3.0), 10};
    assert(cad.cadastrarProduto(semNome).erro == Erro::CampoVazio);
    DadosProduto custoNeg = {"BP-8", "X", "Mercearia", Dinheiro::reais(-1.0), 10};
    assert(cad.cadastrarProduto(custoNeg).erro == Erro::CustoInvalido);
    DadosProduto minNeg = {"BP-9", "Y", "Mercearia", Dinheiro::reais(3.0), -5};
    assert(cad.cadastrarProduto(minNeg).erro == Erro::QuantidadeInvalida);
    assert(banco.buscarProduto("BP-7") == nullptr);    // nada foi criado

    Sessao op(Usuario(31, "Pedro Alves", Perfil::OperadorCaixa, 1));
    ServicoCadastros cadOp(op, banco);
    assert(cadOp.cadastrarProduto(tomate).erro == Erro::AcessoNegado);

    // preco padrao
    assert(cad.definirPrecoPadrao("BP-1265", Dinheiro::reais(11.20)).ok());
    assert(banco.buscarProduto("BP-1265")->preco() == Dinheiro::reais(11.20));

    // precos recusados: o preco anterior continua
    assert(cad.definirPrecoPadrao("BP-1265", Dinheiro::reais(7.00)).erro
           == Erro::PrecoAbaixoDoCusto);
    assert(cad.definirPrecoPadrao("BP-1265", Dinheiro::reais(0.00)).erro
           == Erro::PrecoAbaixoDoCusto);
    assert(cad.definirPrecoPadrao("BP-0000", Dinheiro::reais(5.00)).erro
           == Erro::NaoEncontrado);
    assert(cadOp.definirPrecoPadrao("BP-1265", Dinheiro::reais(9.90)).erro
           == Erro::AcessoNegado);
    assert(banco.buscarProduto("BP-1265")->preco() == Dinheiro::reais(11.20));

    // atualizar o preco
    assert(cad.definirPrecoPadrao("BP-1265", Dinheiro::reais(12.00)).ok());
    assert(banco.buscarProduto("BP-1265")->preco() == Dinheiro::reais(12.00));

    ServicoEstoque estGestor(gestor, banco);
    FiltroEstoque fSemUnidade;
    assert(estGestor.consultarEstoque(fSemUnidade).erro == Erro::UnidadeNaoInformada);
    FiltroEstoque fUnidade1;
    fUnidade1.idUnidade = 1;
    auto cCad = estGestor.consultarEstoque(fUnidade1);
    assert(cCad.ok() && cCad.valor.size() == 1);
    assert(cCad.valor[0].codigoProduto() == "BP-1265");

    std::cout << "  cadastroFuncionalTest OK\n";
}

// ============ Funcional 2: Repositor de Estoque ============
void entradaFuncionalTest() {
    Banco banco;
    montarCatalogo(banco);
    Relogio::fixar(Data(2026, 10, 26));

    Sessao repo(Usuario(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoque estoque(repo, banco);

    // lote 1 e lote 2 do mesmo produto
    Resultado<LoteEstoque> l1 = estoque.registrarEntrada("BP-1265", 30, Data(2026, 10, 30));
    assert(l1.ok() && l1.valor.id() == 1 && l1.valor.saldo() == 30);
    assert(l1.valor.idUnidade() == 1);                     // unidade vem da sessao
    assert(banco.saldoValido(1, "BP-1265", Relogio::hoje()) == 30);

    Resultado<LoteEstoque> l2 = estoque.registrarEntrada("BP-1265", 50, Data(2026, 11, 5));
    assert(l2.ok() && l2.valor.id() == 2);
    assert(banco.saldoValido(1, "BP-1265", Relogio::hoje()) == 80);   // 2 lotes

    Resultado<LoteEstoque> l4 = estoque.registrarEntrada("BP-0720", 40, Data(2026, 12, 15));
    assert(l4.ok() && banco.saldoValido(1, "BP-0720", Relogio::hoje()) == 40);

    // entradas recusadas: nenhum lote novo
    size_t antes = banco.lotes().size();
    assert(estoque.registrarEntrada("BP-1265", 10, Data(2026, 10, 20)).erro == Erro::ValidadeVencida);
    assert(estoque.registrarEntrada("BP-1265", 0,  Data(2026, 11, 5)).erro  == Erro::QuantidadeInvalida);
    assert(estoque.registrarEntrada("BP-0000", 10, Data(2026, 11, 5)).erro  == Erro::NaoEncontrado);

    Sessao op(Usuario(31, "Pedro Alves", Perfil::OperadorCaixa, 1));
    ServicoEstoque estOp(op, banco);
    assert(estOp.registrarEntrada("BP-1265", 5, Data(2026, 12, 1)).erro == Erro::AcessoNegado);
    assert(banco.lotes().size() == antes);

    // o Gerente da unidade tambem pode registrar entrada (na propria unidade)
    Sessao ger(Usuario(41, "Fernanda Alves", Perfil::GerenteUnidade, 1));
    ServicoEstoque estGer(ger, banco);
    assert(estGer.registrarEntrada("BP-0501", 100, Data(2027, 3, 1)).ok());

    FiltroEstoque fRepo;
    auto cRepo = estoque.consultarEstoque(fRepo);
    assert(cRepo.ok());
    for (size_t i = 0; i < cRepo.valor.size(); ++i) {
        if (cRepo.valor[i].codigoProduto() == "BP-0720") {
            assert(cRepo.valor[i].quantidade() == 40);
            assert(cRepo.valor[i].estoqueMinimo() == 60);
            assert(cRepo.valor[i].abaixoDoMinimo());
        }
    }
    FiltroEstoque fOutraUnidade;
    fOutraUnidade.idUnidade = 2;
    assert(estoque.consultarEstoque(fOutraUnidade).erro == Erro::AcessoNegado);

    std::cout << "  entradaFuncionalTest OK\n";
}

// ============ Funcional 3: Operador de Caixa ============
void vendaFuncionalTest() {
    Banco banco;
    montarCatalogo(banco);
    montarLotes(banco);

    Sessao op(Usuario(31, "Pedro Alves", Perfil::OperadorCaixa, 1));
    ServicoEstoque caixa(op, banco);

    Relogio::fixar(Data(2026, 10, 28));
    Resultado<Venda> v1 = caixa.registrarVenda("BP-1265", 2);
    assert(v1.ok());
    assert(v1.valor.valorTotal() == Dinheiro::reais(22.40));
    assert(banco.buscarLote(1)->saldo() == 28 && banco.buscarLote(2)->saldo() == 50);

    Relogio::fixar(Data(2026, 10, 31));
    Resultado<Venda> v2 = caixa.registrarVenda("BP-1265", 2);
    assert(v2.ok() && v2.valor.valorTotal() == Dinheiro::reais(22.40));
    assert(banco.buscarLote(1)->saldo() == 28);
    assert(banco.buscarLote(2)->saldo() == 48);

    size_t vendas = banco.vendas().size();
    assert(caixa.registrarVenda("BP-1265", 60).erro == Erro::EstoqueInsuficiente);
    assert(banco.buscarLote(2)->saldo() == 48);

    Resultado<Venda> v3 = caixa.registrarVenda("BP-1265", 40);
    assert(v3.ok() && v3.valor.valorTotal() == Dinheiro::reais(448.00));
    assert(banco.buscarLote(2)->saldo() == 8 && banco.buscarLote(1)->saldo() == 28);
    assert(banco.vendas().size() == vendas + 1);

    vendas = banco.vendas().size();
    assert(caixa.registrarVenda("BP-1265", 0).erro == Erro::QuantidadeInvalida);
    assert(caixa.registrarVenda("BP-0999", 1).erro == Erro::ProdutoSemPreco);
    assert(caixa.registrarVenda("BP-0000", 1).erro == Erro::NaoEncontrado);

    Sessao repo(Usuario(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoque estRepo(repo, banco);
    assert(estRepo.registrarVenda("BP-1265", 1).erro == Erro::AcessoNegado);

    Sessao op2(Usuario(32, "Lucas Melo", Perfil::OperadorCaixa, 2));
    ServicoEstoque caixa2(op2, banco);
    assert(caixa2.registrarVenda("BP-1265", 1).erro == Erro::EstoqueInsuficiente);
    assert(banco.vendas().size() == vendas);

    FiltroEstoque fVenda;
    fVenda.idUnidade = 1;
    fVenda.categoria = "Hortifruti";
    assert(caixa.consultarEstoque(fVenda).erro == Erro::AcessoNegado);

    Sessao gerVenda(Usuario(41, "Fernanda Alves", Perfil::GerenteUnidade, 1));
    ServicoEstoque estGerVenda(gerVenda, banco);
    auto cVendaGer = estGerVenda.consultarEstoque(fVenda);
    assert(cVendaGer.ok() && cVendaGer.valor.size() == 1);
    assert(cVendaGer.valor[0].quantidade() == 8);
    assert(cVendaGer.valor[0].quantidadeVencida() == 28);
    assert(cVendaGer.valor[0].temValidade());
    assert(cVendaGer.valor[0].validadeMaisProxima() == Data(2026, 11, 5));

    std::cout << "  vendaFuncionalTest OK\n";
}
