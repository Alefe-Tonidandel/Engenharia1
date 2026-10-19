#include "telacadastro.h"
#include "ui_telacadastro.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>

TelaCadastro::TelaCadastro(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TelaCadastro)
{
    ui->setupUi(this);
    this->setWindowTitle("Bom-Preço - Cadastro de Produtos");

    // Configuração Profissional da Tabela
    ui->tabelaProdutos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabelaProdutos->verticalHeader()->setVisible(false);
    ui->tabelaProdutos->setAlternatingRowColors(true);

    // Ajustes dos QDoubleSpinBox (limites até 9999.99 reais)
    ui->spinBoxCusto->setMaximum(9999.99);
    ui->spinBoxPreco->setMaximum(9999.99);
}

TelaCadastro::~TelaCadastro()
{
    delete ui;
}

void TelaCadastro::on_btnCadastrar_clicked()
{
    // 1. Captura os dados da interface
    QString nome = ui->lineEditNome->text().trimmed();
    double custo = ui->spinBoxCusto->value();
    double preco = ui->spinBoxPreco->value();

    // 2. Validações de Negócio
    if(nome.isEmpty()) {
        QMessageBox::warning(this, "Atenção", "O nome do produto é obrigatório.");
        ui->lineEditNome->setFocus();
        return;
    }

    if(preco <= 0) {
        QMessageBox::warning(this, "Atenção", "O preço de venda deve ser maior que zero.");
        ui->spinBoxPreco->setFocus();
        return;
    }

    if(custo >= preco) {
        // Um aviso amigável, pois num supermercado raramente se vende com prejuízo
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this, "Confirmação de Margem",
                                         "O custo é maior ou igual ao preço de venda. Deseja cadastrar mesmo assim?",
                                         QMessageBox::Yes | QMessageBox::No);
        if(resposta == QMessageBox::No) {
            return; // Cancela o cadastro se o utilizador clicar em Não
        }
    }

    // 3. Adiciona na Tabela
    int row = ui->tabelaProdutos->rowCount();
    ui->tabelaProdutos->insertRow(row);

    ui->tabelaProdutos->setItem(row, 0, new QTableWidgetItem(nome));
    ui->tabelaProdutos->setItem(row, 1, new QTableWidgetItem(QString("R$ %1").arg(custo, 0, 'f', 2)));
    ui->tabelaProdutos->setItem(row, 2, new QTableWidgetItem(QString("R$ %1").arg(preco, 0, 'f', 2)));

    // 4. Feedback e Limpeza do Formulário para o próximo produto
    QMessageBox::information(this, "Sucesso", "Produto cadastrado no catálogo!");

    ui->lineEditNome->clear();
    ui->spinBoxCusto->setValue(0.0);
    ui->spinBoxPreco->setValue(0.0);
    ui->lineEditNome->setFocus();
}