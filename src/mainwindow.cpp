#include "mainwindow.h"
#include "menuprincipal.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// O Qt cria esse nome automaticamente quando você usa o "Go to slot..." no botão btnLogin
void MainWindow::on_btnLogin_clicked()
{
    // Captura o que foi digitado nos campos de texto
    QString usuario = ui->lineEditUser->text();
    QString senha = ui->lineEditPassword->text();

    // Validação estática temporária (futuramente você fará uma consulta no banco de dados)
    if (usuario == "admin" && senha == "1234") {

        // Se as credenciais estiverem corretas, abre o Menu Principal
        MenuPrincipal *menu = new MenuPrincipal();
        menu->show();

        this->hide(); // Esconde a tela de login

    } else {

        // Se estiverem erradas, mostra um alerta profissional
        QMessageBox::warning(this, "Erro de Autenticação", "Usuário ou senha incorretos.");

        // Limpa o campo de senha para o usuário tentar novamente
        ui->lineEditPassword->clear();
        ui->lineEditUser->setFocus(); // Volta o cursor para o campo de usuário
    }
}