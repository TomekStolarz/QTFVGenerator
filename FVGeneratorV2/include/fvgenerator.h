#ifndef FVGENERATOR_H
#define FVGENERATOR_H

#include "lastid.h"
#include <string>
#include "database.h"
#include "producent.h"
#include <QMainWindow>
#include "createcustomerdialog.h"
#include "createfvdialog.h"
#include "createitemdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FVGenerator; }
QT_END_NAMESPACE

class FVGenerator : public QMainWindow
{
    Q_OBJECT

public:
    FVGenerator(QWidget *parent = nullptr);
    ~FVGenerator();
private slots:
   void on_BtnAddCustomer_clicked();

    void on_BtnCreate_clicked();

    void on_BtnAddItem_clicked();

    void on_BtnExit_clicked();

private:
    Ui::FVGenerator *ui;
};
#endif // FVGENERATOR_H
