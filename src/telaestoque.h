#ifndef TELAESTOQUE_H
#define TELAESTOQUE_H

#include <QDialog>

namespace Ui {
class TelaEstoque;
}

class TelaEstoque : public QDialog
{
    Q_OBJECT

public:
    explicit TelaEstoque(QWidget *parent = nullptr);
    ~TelaEstoque();

private slots:
    void on_btnRegistrarEntrada_clicked();
    void on_btnRegistrarPerda_clicked();

private:
    Ui::TelaEstoque *ui;
};

#endif // TELAESTOQUE_H