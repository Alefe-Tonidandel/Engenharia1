#include "telaestoque.h"
#include "ui_telaestoque.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDate> // Necessário para manipular datas

TelaEstoque::TelaEstoque(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TelaEstoque)
{
    ui->setupUi(this);
    this->setWindowTitle("Bom-Preço - Gestão de Estoque");

    // Configuração Profissional da Tabela
    ui->tabelaEstoque->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabelaEstoque->verticalHeader()->setVisible(false);
    ui->tabelaEstoque->setAlternatingRowColors(true);

    // Ajustes padrão da interface
    ui->dateEditEntradaVencimento->setDate(QDate::currentDate().addMonths(6)); // Sugere validade de 6 meses
    ui->spinBoxEntradaQtd->setMaximum(10000); // Permite receber até 10.000 itens de uma vez
    ui->spinBoxPerdaQtd->setMaximum(10000);

    // Populando alguns dados iniciais para visualização
    ui->tabelaEstoque->setRowCount(2);
    ui->tabelaEstoque->setItem(0, 0, new QTableWidgetItem("arroz"));
    ui->tabelaEstoque->setItem(0, 1, new QTableWidgetItem("50"));
    ui->tabelaEstoque->setItem(0, 2, new QTableWidgetItem(QDate::currentDate().addMonths(12).toString("dd/MM/yyyy")));

    ui->tabelaEstoque->setItem(1, 0, new QTableWidgetItem("feijão"));
    ui->tabelaEstoque->setItem(1, 1, new QTableWidgetItem("30"));
    ui->tabelaEstoque->setItem(1, 2, new QTableWidgetItem(QDate::currentDate().addMonths(8).toString("dd/MM/yyyy")));
}

TelaEstoque::~TelaEstoque()
{
    delete ui;
}

void TelaEstoque::on_btnRegistrarEntrada_clicked()
{
    QString nome = ui->lineEditEntradaProduto->text().toLower().trimmed();
    int qtdEntrada = ui->spinBoxEntradaQtd->value();
    QString vencimento = ui->dateEditEntradaVencimento->date().toString("dd/MM/yyyy");

    if (nome.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "Por favor, digite o nome do produto recebido.");
        return;
    }

    // Procura se o produto já existe na tabela para somar a quantidade
    bool produtoEncontrado = false;
    for (int i = 0; i < ui->tabelaEstoque->rowCount(); ++i) {
        if (ui->tabelaEstoque->item(i, 0)->text().toLower() == nome) {
            int qtdAtual = ui->tabelaEstoque->item(i, 1)->text().toInt();
            ui->tabelaEstoque->item(i, 1)->setText(QString::number(qtdAtual + qtdEntrada));

            // Atualiza a data de vencimento para a do lote mais recente
            ui->tabelaEstoque->item(i, 2)->setText(vencimento);
            produtoEncontrado = true;
            break;
        }
    }

    // Se for um produto novo no armazém, adiciona uma linha nova
    if (!produtoEncontrado) {
        int row = ui->tabelaEstoque->rowCount();
        ui->tabelaEstoque->insertRow(row);
        ui->tabelaEstoque->setItem(row, 0, new QTableWidgetItem(nome));
        ui->tabelaEstoque->setItem(row, 1, new QTableWidgetItem(QString::number(qtdEntrada)));
        ui->tabelaEstoque->setItem(row, 2, new QTableWidgetItem(vencimento));
    }

    QMessageBox::information(this, "Sucesso", "Entrada de estoque registrada com sucesso!");
    ui->lineEditEntradaProduto->clear();
    ui->spinBoxEntradaQtd->setValue(1);
    ui->lineEditEntradaProduto->setFocus();
}

void TelaEstoque::on_btnRegistrarPerda_clicked()
{
    QString nome = ui->lineEditPerdaProduto->text().toLower().trimmed();
    int qtdPerda = ui->spinBoxPerdaQtd->value();
    QString motivo = ui->comboBoxPerdaMotivo->currentText();

    if (nome.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "Digite o nome do produto para registrar a baixa.");
        return;
    }

    bool produtoEncontrado = false;
    for (int i = 0; i < ui->tabelaEstoque->rowCount(); ++i) {
        if (ui->tabelaEstoque->item(i, 0)->text().toLower() == nome) {
            int qtdAtual = ui->tabelaEstoque->item(i, 1)->text().toInt();

            // Validação de negócio: Não pode dar baixa de mais itens do que os que existem
            if (qtdPerda > qtdAtual) {
                QMessageBox::critical(this, "Erro de Operação", QString("Quantidade inválida! Existem apenas %1 unidades de '%2' no estoque.").arg(qtdAtual).arg(nome));
                return;
            }

            // Subtrai a quantidade
            ui->tabelaEstoque->item(i, 1)->setText(QString::number(qtdAtual - qtdPerda));
            produtoEncontrado = true;

            QMessageBox::information(this, "Baixa Registrada", QString("%1 unidade(s) de '%2' removidas.\nMotivo: %3").arg(qtdPerda).arg(nome).arg(motivo));
            break;
        }
    }

    if (!produtoEncontrado) {
        QMessageBox::warning(this, "Não Encontrado", "O produto digitado não existe no estoque atual.");
    }

    ui->lineEditPerdaProduto->clear();
    ui->spinBoxPerdaQtd->setValue(1);
    ui->comboBoxPerdaMotivo->setCurrentIndex(0);
}