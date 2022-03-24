#ifndef CREATEFVDIALOG_H
#define CREATEFVDIALOG_H

#include <QDialog>
#include "database.h"
#include "customer.h"
#include "item.h"
#include <vector>
#include <string>
#include <QStringListModel>
#include "item.h"
#include <QInputDialog>
#include <QStandardItemModel>
#include "fvgenerator.h"
#include "fvorder.h"
#include <QPrinter>
#include <QApplication>


namespace Ui {
class CreateFVDialog;
}

class CreateFVDialog : public QDialog
{
    Q_OBJECT
      QStringListModel *customersListModel;
      QStringListModel *itemsListModel;
      QStandardItemModel *tableViewModel;
public:
    explicit CreateFVDialog(QWidget *parent = nullptr);
    ~CreateFVDialog();
    void loadCusomters();
    void loadItems();
    void setTableWidget(QStandardItemModel *countriesTableModel, const Item &toAdd, int quantity);
    Customer getCurrentCustomer(bool &selected);
    vector<itemsList> getItemsList();
    QString getHtmlPrintString(const FVOrder &fvorder, const Customer &customer);
    QString createTableHtmlString(FVOrder fvorder);
private slots:
    void on_ListViewItem_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::CreateFVDialog *ui;
};

#endif // CREATEFVDIALOG_H
