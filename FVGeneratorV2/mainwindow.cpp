#include "mainwindow.h"
#include "./ui_mainwindow.h"

extern Producent owner;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tableItemViewModel = new QStandardItemModel(ui->TableDisplay);
    tableCustomerViewModel = new QStandardItemModel(ui->TableDisplay);
    ui->TableDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers); //bez edycji pol
    ui->TableDisplay->setSelectionBehavior(QAbstractItemView::SelectRows); // ustawiam zaznaczanie całych wierszy
    ui->TableDisplay->setSelectionMode(QAbstractItemView::SingleSelection);//pojedynczy wybor
    ui->label_2->setText(QString::fromStdString("Hello " + owner.getLogin() + "\n") + QDate::currentDate().toString("dd.MM.yyyy"));
}

MainWindow::~MainWindow()
{
    if(!LastId::getIsSaved())
    {
        vector<string> toSave;
        Database lastIdSave("../data/lastid.csv", 3);
        toSave.push_back(std::to_string(LastId::getCustomerLastId()));
        toSave.push_back(std::to_string(LastId::getItemLastId()));
        lastIdSave.saveData(toSave);
        lastIdSave.close();
    }
    delete ui;
}


void MainWindow::on_BtnAddCustomer_clicked()
{
    CreateCustomerDialog customerDialog;
    customerDialog.setModal(true);
    customerDialog.exec();
}


void MainWindow::on_BtnAddItem_clicked()
{
    CreateItemDialog itemDialog;
    itemDialog.setModal(true);
    itemDialog.exec();
}


void MainWindow::on_BtnExit_clicked()
{
    QCoreApplication::quit();
}


void MainWindow::on_BtnCreate_clicked()
{
    CreateFVDialog fvDialog;
    fvDialog.setModal(true);
    fvDialog.exec();
}


void MainWindow::on_BtnDspItem_clicked()
{
    tableItemViewModel->clear();
    tableItemViewModel->setColumnCount(5);
    tableItemViewModel->setHorizontalHeaderLabels(
                                                   {"Item Id", "Name", "Price", "Vat", "Qunatity Type"}
                                                 );

    Database dbLoadItems("items.csv", 0);
    vector<Item> items = dbLoadItems.getRecords<Item>();
    dbLoadItems.close();

    for(Item &itm :items)
    {
        setTableWidget(tableItemViewModel, itm);
    }

    ui->TableDisplay->setModel(tableItemViewModel);
    items.clear();
    items.shrink_to_fit();

}


void MainWindow::setTableWidget(QStandardItemModel *itemsTableModel, const Item &toAdd)
{
        int index = itemsTableModel->rowCount();
       itemsTableModel->setRowCount(index + 1);

       QStandardItem *itemId = new QStandardItem(QString::fromStdString(std::to_string(toAdd.getId())));
       itemsTableModel->setItem(index, 0, itemId);

       QStandardItem *itemName = new QStandardItem(QString::fromStdString(toAdd.getName()));
       itemsTableModel->setItem(index, 1, itemName);

       QStandardItem *itemPrice = new QStandardItem(QString::fromStdString(std::to_string(toAdd.getPrice())));
       itemsTableModel->setItem(index, 2, itemPrice);

       QStandardItem *itemQuantity = new QStandardItem(QString::fromStdString(std::to_string(toAdd.getVat())));
       itemsTableModel->setItem(index, 3, itemQuantity);

       QStandardItem *itemSum = new QStandardItem(QString::fromStdString(toAdd.getQuantityType()));
       itemsTableModel->setItem(index, 4, itemSum);
}


void MainWindow::on_BtnDspCustomer_clicked()
{
    tableCustomerViewModel->clear();
    tableCustomerViewModel->setColumnCount(4);
    tableCustomerViewModel->setHorizontalHeaderLabels(
                                                   {"Customer Id", "Name", "Last Name", "Nip"}
                                                 );

    Database dbLoadCustomers("customers.csv", 0);
    vector<Customer> customers = dbLoadCustomers.getRecords<Customer>();
    dbLoadCustomers.close();

    for(Customer &cst :customers)
    {
        setTableWidget(tableCustomerViewModel, cst);
    }

    customers.clear();
    customers.shrink_to_fit();

    ui->TableDisplay->setModel(tableCustomerViewModel);
}

void MainWindow::setTableWidget(QStandardItemModel *customerTableModel, const Customer &toAdd)
{
        int index = customerTableModel->rowCount();
       customerTableModel->setRowCount(index + 1);

       QStandardItem *customerId = new QStandardItem(QString::fromStdString(std::to_string(toAdd.getId())));
       customerTableModel->setItem(index, 0, customerId);

       QStandardItem *customerName = new QStandardItem(QString::fromStdString(toAdd.getName()));
       customerTableModel->setItem(index, 1, customerName);

       QStandardItem *customerPrice = new QStandardItem(QString::fromStdString(toAdd.getLastName()));
       customerTableModel->setItem(index, 2, customerPrice);

       QStandardItem *customerQuantity = new QStandardItem(QString::fromStdString(std::to_string(toAdd.getNip())));
       customerTableModel->setItem(index, 3, customerQuantity);
}

