#ifndef CREATEITEMDIALOG_H
#define CREATEITEMDIALOG_H

#include <QDialog>
#include "item.h"
#include <string>

namespace Ui {
class CreateItemDialog;
}

class CreateItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateItemDialog(QWidget *parent = nullptr);
    ~CreateItemDialog();

private slots:
    void on_BtnAdd_clicked();

private:
    Ui::CreateItemDialog *ui;
};

#endif // CREATEITEMDIALOG_H
