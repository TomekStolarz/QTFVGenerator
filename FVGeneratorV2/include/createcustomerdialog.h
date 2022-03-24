#ifndef CREATECUSTOMERDIALOG_H
#define CREATECUSTOMERDIALOG_H

#include <QDialog>
#include <QRegularExpression>
#include <string>
#include "address.h"
#include "customer.h"

namespace Ui {
class CreateCustomerDialog;
}

class CreateCustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateCustomerDialog(QWidget *parent = nullptr);
    ~CreateCustomerDialog();

private slots:

    void on_BtnAdd_clicked();

    void on_chxCompany_stateChanged(int arg1);

private:
    Ui::CreateCustomerDialog *ui;
};

#endif // CREATECUSTOMERDIALOG_H
