#include "telacaixa.h"
#include "ui_telacaixa.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>

TelaCaixa::TelaCaixa(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TelaCaixa)
{
    ui->setupUi(this);
    this->setWindowTitle("Bom-Preço - Operador de Caixa"); // Título profissional
    totalVenda = 0.0;

    // Ajustes profissionais da tabela
    ui->tabelaVendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Preenche o espaço
    ui->tabelaVendas->verticalHeader()->setVisible(false); // Esconde os números das linhas ao lado
    ui->tabelaVendas->setAlternatingRowColors(true); // Facilita a leitura

    // Populando nosso "Banco de Dados" simulado para testar
    bancoDeProdutos.insert("arroz", 15.50);
    bancoDeProdutos.insert("batata", 5.90);
    bancoDeProdutos.insert("feijão", 8.90);
    bancoDeProdutos.insert("leite", 4.50);
}

TelaCaixa::~TelaCaixa()
{
    delete ui;
}

void TelaCaixa::recalcularTotal()
{
    totalVenda = 0.0;
    // Percorre todas as linhas da tabela e soma a coluna 3 (Subtotal)
    for(int i = 0; i < ui->tabelaVendas->rowCount(); ++i) {
        double subtotalDaLinha = ui->tabelaVendas->item(i, 3)->text().toDouble();
        totalVenda += subtotalDaLinha;
    }
    ui->lblTotal->setText(QString("Total: R$ %1").arg(totalVenda, 0, 'f', 2));
}

void TelaCaixa::on_btnAdicionar_clicked()
{
    QString nomeProduto = ui->lineEditProduto->text().toLower().trimmed();

    if(nomeProduto.isEmpty()){
        QMessageBox::warning(this, "Aviso", "Por favor, digite o nome do produto.");
        return;
    }

    // Procura o produto no "Banco de Dados"
    if(!bancoDeProdutos.contains(nomeProduto)) {
        QMessageBox::warning(this, "Erro", "Produto não encontrado no sistema.");
        ui->lineEditProduto->selectAll();
        return;
    }

    double precoUnitario = bancoDeProdutos.value(nomeProduto);
    int quantidade = 1; // Por defeito adiciona 1, mas numa versão avançada teríamos um QSpinBox para a Qtd

    // Verifica se o produto já está na tabela para apenas somar a quantidade
    bool produtoJaExiste = false;
    for(int i = 0; i < ui->tabelaVendas->rowCount(); ++i) {
        if(ui->tabelaVendas->item(i, 0)->text().toLower() == nomeProduto) {

            // Atualiza a quantidade
            int qtdAtual = ui->tabelaVendas->item(i, 1)->text().toInt();
            qtdAtual += quantidade;
            ui->tabelaVendas->item(i, 1)->setText(QString::number(qtdAtual));

            // Atualiza o subtotal da linha corretamente
            double novoSubtotal = qtdAtual * precoUnitario;
            ui->tabelaVendas->item(i, 3)->setText(QString::number(novoSubtotal, 'f', 2));

            produtoJaExiste = true;
            break;
        }
    }

    // Se o produto não estava na tabela, cria uma nova linha
    if(!produtoJaExiste) {
        int row = ui->tabelaVendas->rowCount();
        ui->tabelaVendas->insertRow(row);

        // Bloqueia individualmente os itens (dupla segurança) e formata
        QTableWidgetItem *itemNome = new QTableWidgetItem(nomeProduto);
        QTableWidgetItem *itemQtd = new QTableWidgetItem(QString::number(quantidade));
        QTableWidgetItem *itemPreco = new QTableWidgetItem(QString::number(precoUnitario, 'f', 2));
        QTableWidgetItem *itemSubtotal = new QTableWidgetItem(QString::number(precoUnitario * quantidade, 'f', 2));

        ui->tabelaVendas->setItem(row, 0, itemNome);
        ui->tabelaVendas->setItem(row, 1, itemQtd);
        ui->tabelaVendas->setItem(row, 2, itemPreco);
        ui->tabelaVendas->setItem(row, 3, itemSubtotal);
    }

    recalcularTotal();

    // Prepara para o próximo item
    ui->lineEditProduto->clear();
    ui->lineEditProduto->setFocus();
}

void TelaCaixa::on_btnFinalizar_clicked()
{
    if(ui->tabelaVendas->rowCount() == 0) {
        QMessageBox::information(this, "Caixa", "Não há produtos registrados para pagamento.");
        return;
    }

    QMessageBox::information(this, "Pagamento", QString("Pagamento de R$ %1 processado com sucesso.\nEstoque atualizado.").arg(totalVenda, 0, 'f', 2));

    // Reset da interface
    ui->tabelaVendas->setRowCount(0);
    recalcularTotal();
    ui->lineEditProduto->setFocus();
}