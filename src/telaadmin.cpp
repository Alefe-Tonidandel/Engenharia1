#include "telaadmin.h"
#include "ui_telaadmin.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>

TelaAdmin::TelaAdmin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TelaAdmin)
{
    ui->setupUi(this);
    this->setWindowTitle("Administração da Rede");

    // Configurar tabela de Utilizadores
    ui->tabelaUsuarios->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabelaUsuarios->verticalHeader()->setVisible(false);

    // Configurar tabela de Unidades
    ui->tabelaUnidades->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabelaUnidades->verticalHeader()->setVisible(false);

    // Adicionar itens de exemplo nos ComboBoxes
    ui->comboPerfilUser->addItems({"Gerente da Unidade", "Operador de Caixa", "Repositor de Estoque", "Gestor da Rede"});
    ui->comboUnidadeUser->addItems({"Todas (Acesso Total)", "Unidade Norte", "Unidade Sul", "Unidade Centro"});
}

TelaAdmin::~TelaAdmin()
{
    delete ui;
}

void TelaAdmin::on_btnSalvarUser_clicked()
{
    QString nome = ui->lineEditNomeUser->text().trimmed();
    QString email = ui->lineEditEmailUser->text().trimmed();

    if(nome.isEmpty() || email.isEmpty()){
        QMessageBox::warning(this, "Aviso", "Preencha o Nome e o E-mail.");
        return;
    }

    int row = ui->tabelaUsuarios->rowCount();
    ui->tabelaUsuarios->insertRow(row);
    ui->tabelaUsuarios->setItem(row, 0, new QTableWidgetItem(nome));
    ui->tabelaUsuarios->setItem(row, 1, new QTableWidgetItem(email));
    ui->tabelaUsuarios->setItem(row, 2, new QTableWidgetItem(ui->comboPerfilUser->currentText()));
    ui->tabelaUsuarios->setItem(row, 3, new QTableWidgetItem(ui->comboUnidadeUser->currentText()));

    QMessageBox::information(this, "Sucesso", "Usuário cadastrado com sucesso!");
    ui->lineEditNomeUser->clear();
    ui->lineEditEmailUser->clear();
}

void TelaAdmin::on_btnSalvarUni_clicked()
{
    QString codigo = ui->lineEditCodigoUni->text().trimmed();
    QString nome = ui->lineEditNomeUni->text().trimmed();

    if(codigo.isEmpty() || nome.isEmpty()){
        QMessageBox::warning(this, "Aviso", "Preencha o Código e o Nome da Unidade.");
        return;
    }

    int row = ui->tabelaUnidades->rowCount();
    ui->tabelaUnidades->insertRow(row);
    ui->tabelaUnidades->setItem(row, 0, new QTableWidgetItem(codigo));
    ui->tabelaUnidades->setItem(row, 1, new QTableWidgetItem(nome));
    ui->tabelaUnidades->setItem(row, 2, new QTableWidgetItem(ui->lineEditEnderecoUni->text()));

    QMessageBox::information(this, "Sucesso", "Unidade cadastrada com sucesso!");
    ui->lineEditCodigoUni->clear();
    ui->lineEditNomeUni->clear();
    ui->lineEditEnderecoUni->clear();
}