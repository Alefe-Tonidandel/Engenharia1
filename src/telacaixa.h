#ifndef TELACAIXA_H
#define TELACAIXA_H

#include <QDialog>
#include <QMap>

namespace Ui {
class TelaCaixa;
}

class TelaCaixa : public QDialog
{
    Q_OBJECT

public:
    explicit TelaCaixa(QWidget *parent = nullptr);
    ~TelaCaixa();

private slots:
    void on_btnAdicionar_clicked();
    void on_btnFinalizar_clicked();

private:
    Ui::TelaCaixa *ui;
    double totalVenda;

    // Simulação do Banco de Dados de Produtos (Nome -> Preço)
    QMap<QString, double> bancoDeProdutos;

    void recalcularTotal(); // Função dedicada para evitar erros de soma
};

#endif // TELACAIXA_H