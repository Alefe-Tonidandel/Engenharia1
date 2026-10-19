#ifndef TELAADMIN_H
#define TELAADMIN_H

#include <QDialog>

namespace Ui {
class TelaAdmin;
}

class TelaAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit TelaAdmin(QWidget *parent = nullptr);
    ~TelaAdmin();

private slots:
    void on_btnSalvarUser_clicked();
    void on_btnSalvarUni_clicked();

private:
    Ui::TelaAdmin *ui;
};

#endif // TELAADMIN_H