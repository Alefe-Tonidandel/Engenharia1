#ifndef TELACADASTRO_H
#define TELACADASTRO_H

#include <QDialog>

namespace Ui {
class TelaCadastro;
}

class TelaCadastro : public QDialog
{
    Q_OBJECT

public:
    explicit TelaCadastro(QWidget *parent = nullptr);
    ~TelaCadastro();

private slots:
    void on_btnCadastrar_clicked(); // Função do nosso botão

private:
    Ui::TelaCadastro *ui;
};

#endif // TELACADASTRO_H