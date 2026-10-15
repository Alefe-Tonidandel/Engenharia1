// ===========================================================================
// Testes do Bom-Preço Administração - ESBOÇO (Sprint 1)
//
// Uma função de teste para cada funcionalidade [S1] do documento de requisitos.
// Por enquanto as funcionalidades ainda não existem, então os testes estão
// marcados com QSKIP ("pulado"). Conforme cada tela ficar pronta, troca o
// QSKIP pelo teste de verdade.
// ===========================================================================
#include <QtTest>

class TestBomPreco : public QObject
{
    Q_OBJECT

private slots:
    // Teste simples só para mostrar que o ambiente de testes funciona
    void ambienteFunciona();

    void registrarEntradaProdutos();
    void consultarEstoque();
    void registrarVenda();
};

void TestBomPreco::registrarEntradaProdutos()
{
    // TODO: dar entrada de 50 unidades e verificar se o estoque aumentou
    QSKIP("A implementar - entrada de produtos");
}

void TestBomPreco::consultarEstoque()
{
    // TODO: buscar um produto e verificar a quantidade mostrada
    QSKIP("A implementar - consulta de estoque");
}

void TestBomPreco::registrarVenda()
{
    // TODO: vender 2 unidades e verificar se o estoque diminuiu
    QSKIP("A implementar - tela de caixa");
}

QTEST_MAIN(TestBomPreco)
#include "tst_bompreco.moc"
