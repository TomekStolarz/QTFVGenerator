#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include "createcustomerdialog.h"
#include "createitemdialog.h"
#include "createfvdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStandardItemModel *tableItemViewModel;
    QStandardItemModel *tableCustomerViewModel;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTableWidget(QStandardItemModel *itemsTableModel, const Item &toAdd);
    void setTableWidget(QStandardItemModel *customersTableModel, const Customer &toAdd);
private slots:
    void on_BtnAddCustomer_clicked();

    void on_BtnAddItem_clicked();

    void on_BtnExit_clicked();

    void on_BtnCreate_clicked();

    void on_BtnDspItem_clicked();

    void on_BtnDspCustomer_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
