#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QDialog>

namespace Ui {
class MenuPrincipal;
}

class MenuPrincipal : public QDialog
{
    Q_OBJECT

public:
    explicit MenuPrincipal(QWidget *parent = nullptr);
    ~MenuPrincipal();

private slots:
    void on_pushButton_5_clicked(); // Botão Caixa
    void on_pushButton_4_clicked(); // Botão Estoque
    void on_pushButton_2_clicked(); // Botão Cadastros
    void on_pushButton_3_clicked(); // Botão Sair
    void on_btnAdmin_clicked();

private:
    Ui::MenuPrincipal *ui;
};

#endif // MENUPRINCIPAL_H