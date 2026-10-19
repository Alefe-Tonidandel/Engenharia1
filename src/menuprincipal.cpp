#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include "telacaixa.h"
#include "telaestoque.h"
#include "telacadastro.h"
#include "telaadmin.h"
#include <QApplication> // Necessário para o botão de sair

MenuPrincipal::MenuPrincipal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuPrincipal)
{
    ui->setupUi(this);
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

// Lógica do Botão Caixa (pushButton_5 no seu UI)
void MenuPrincipal::on_pushButton_5_clicked()
{
    TelaCaixa *caixa = new TelaCaixa();
    caixa->show();
}

// Lógica do Botão Estoque (pushButton_4 no seu UI)
void MenuPrincipal::on_pushButton_4_clicked()
{
     TelaEstoque *estoque = new TelaEstoque();
     estoque->show();
}

// Lógica do Botão Cadastros (pushButton_2 no seu UI)
void MenuPrincipal::on_pushButton_2_clicked()
{
     TelaCadastro *cadastros = new TelaCadastro();
     cadastros->show();
}

// Lógica do Botão Sair do Sistema (pushButton_3 no seu UI)
void MenuPrincipal::on_pushButton_3_clicked()
{
    QApplication::quit(); // Fecha o programa completamente
}

void MenuPrincipal::on_btnAdmin_clicked() {
    TelaAdmin *admin = new TelaAdmin();
    admin->show();
}