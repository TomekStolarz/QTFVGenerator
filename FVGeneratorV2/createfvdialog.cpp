#include "createfvdialog.h"
#include "ui_createfvdialog.h"
#include <QFile>

extern Producent owner;

CreateFVDialog::CreateFVDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateFVDialog)
{
    ui->setupUi(this);
    ui->RdBtnOnline->setChecked(true);
    tableViewModel = new QStandardItemModel(ui->tableView);
    ui->tableView->setModel(tableViewModel);
    tableViewModel->setColumnCount(5);
    tableViewModel->setHorizontalHeaderLabels(
                                                   {"Item Id", "Name", "Quantity", "Price", "Sum"}
                                                 );
    ui->LstCustomers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ListViewItem->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //bez edycji pol
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // ustawiam zaznaczanie całych wierszy
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // ustawiam możliwość zaznaczania pojedynczego rekordu
    loadCusomters();
    loadItems();
}

CreateFVDialog::~CreateFVDialog()
{
    delete ui;
}

void CreateFVDialog::on_ListViewItem_doubleClicked(const QModelIndex &index)
{
    int id = index.row() + 1;
    bool ok = false;
    int count = QInputDialog::getInt(this, "Count", "Type a quantity of item", 0, 0 , 2147483647, 1, &ok, Qt::MSWindowsFixedSizeDialogHint);
    if(!ok || count <= 0)
        return;
    Database dbLoadItems("items.csv", 0);
    Item itemToAdd = dbLoadItems.getRecord<Item>(id);
    dbLoadItems.close();
    setTableWidget(tableViewModel, itemToAdd, count);
}

void CreateFVDialog::setTableWidget(QStandardItemModel *itemsTableModel, const Item &toAdd, int quantity)
{
        int index = itemsTableModel->rowCount();
       itemsTableModel->setRowCount(index + 1);

       QStandardItem *itemId = new QStandardItem(QString::fromStdString(std::to_string(toAdd.getId())));
       itemsTableModel->setItem(index, 0, itemId);

       QStandardItem *itemName = new QStandardItem(QString::fromStdString(toAdd.getName()));
       itemsTableModel->setItem(index, 1, itemName);

       QStandardItem *itemQuantity = new QStandardItem(QString::fromStdString(std::to_string(quantity)));
       itemsTableModel->setItem(index, 2, itemQuantity);

       QStandardItem *itemPrice = new QStandardItem(QString::fromStdString(std::to_string(toAdd.getPrice())));
       itemsTableModel->setItem(index, 3, itemPrice);

       QStandardItem *itemSum = new QStandardItem(QString::fromStdString(std::to_string(toAdd.getPrice() * quantity)));
       itemsTableModel->setItem(index, 4, itemSum);
}

void CreateFVDialog::loadCusomters()
{
    Database dbLoadCustomers("customers.csv", 0);
    vector<Customer> customers = dbLoadCustomers.getRecords<Customer>();
    dbLoadCustomers.close();

    customersListModel = new QStringListModel(this);

    for(Customer &cst :customers)
    {
        customersListModel->insertRow ( customersListModel->rowCount() );
        QModelIndex index = customersListModel->index(customersListModel->rowCount() - 1, 0);
        customersListModel->setData(index , QString::fromStdString(cst.getName()));
    }
    ui->LstCustomers->setModel(customersListModel);
    ui->LstCustomers->setSelectionMode(QAbstractItemView::SingleSelection);
    customers.clear();
    customers.shrink_to_fit();
}

void CreateFVDialog::loadItems()
{
    Database dbLoadItems("items.csv", 0);
    vector<Item> items = dbLoadItems.getRecords<Item>();
    dbLoadItems.close();

    itemsListModel = new QStringListModel(this);

    for(Item &itm :items)
    {
        itemsListModel->insertRow ( itemsListModel->rowCount() );
        QModelIndex index = itemsListModel->index(itemsListModel->rowCount() - 1, 0);
        itemsListModel->setData(index , QString::fromStdString(itm.getName()));
    }
    ui->ListViewItem->setModel(itemsListModel);
    items.clear();
    items.shrink_to_fit();
}


void CreateFVDialog::on_pushButton_clicked()
{
    bool valid = false;
    ui->LblCustErr->setText("");
    ui->LblItemErr->setText("");
    Customer currentCustomer = getCurrentCustomer(valid);

    if(!valid)
    {
        ui->LblCustErr->setText("Select customer!");
        return;
    }
    if(tableViewModel->rowCount() == 0)
    {
        ui->LblItemErr->setText("Add items!");
        return;
    }


    int paymentOpt = 0;
    if(!ui->RdBtnOnline->isChecked())
        paymentOpt = 1;
    int discount = ui->LblDiscount->text().toInt();

    vector<itemsList> items = getItemsList();
    if(items.size() == 0)
        return;

    FVOrder FVToPrint(currentCustomer.getId(), owner.getLogin(), paymentOpt, items, discount);

    QString html = getHtmlPrintString(FVToPrint, currentCustomer);
    QTextDocument document;
    document.setHtml(html);

    QFile qHtmlFile("D:\\Qt\\projects\\FVGeneratorV2\\fv\\"+ QString::fromStdString(FVToPrint.getFVId()) +".html");
    if(qHtmlFile.open(QIODevice::WriteOnly))
    {
        qHtmlFile.write(html.toUtf8());
        qHtmlFile.close();
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    QString fvname = "D:\\Qt\\projects\\FVGeneratorV2\\fv\\" + QString::fromStdString(FVToPrint.getFVId()) + ".pdf";
    printer.setOutputFileName(fvname);
    printer.setPageMargins(QMarginsF(5, 5, 5, 5));

    document.print(&printer);
    close();
}

QString CreateFVDialog::getHtmlPrintString(const FVOrder &fvorder, const Customer &customer)
{
    QString html;
    html ="<!DOCTYPE html><html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><style type='text/css'>table, tr, td{border: 1px solid black; border-collapse:collapse;} td{padding:1%;}</style></head>";
    html += "<body>";
    html += "<table width='100%'><tr width='100%'><td width='100%'><table style='float:left; border: 2px solid black; width:42%; margin-right:2%; margin-left:2%; padding:2%; height:5%;'><tr><td><h2><b>";
    html += QString::fromStdString(fvorder.getFVId());
    html += "</b></h2></td></tr></table><table style='float:left; padding:2%; margin-right:2%; border: 2px solid black; width:42%; height:5%;'><tr><td>";
    html +=  QString::fromStdString(fvorder.getDate());
    html += "</td></tr></table><table style='clear:both; border-style:none;'></table><table style='float:left; border: 2px solid black; width:42%; margin-right:2%; margin-top:1%; margin-left:2%; padding:2%; height:15%;'><tr><td>";
    html += QString::fromStdString(owner.getName() + "<br> Nip: " + std::to_string(owner.getNip()) + "<br> Phone: " + owner.getPhone());
    html += QString::fromStdString("<br> Email: " +owner.getEmail());
    if(owner.getWebPage() != "")
        html += QString::fromStdString("<br> Web page: " + owner.getWebPage());
    if(owner.getFax() != "")
        html += QString::fromStdString("<br> Fax: " + owner.getFax());
    html += "<br>";
    html += QString::fromStdString(owner.getAddress().getAddressTemplete());
    html += "</td></tr></table><table style='float:left; margin-top:1%; padding:2%; margin-right:2%; border: 2px solid black; width:42%; height:15%;'><tr><td>";
    html += "Customer: <br> Name: ";
    html += QString::fromStdString(customer.getName() + " ");
    if(customer.getType())
        html += QString::fromStdString(customer.getLastName());
    else
        html += QString::fromStdString("<br> Nip: " + to_string(customer.getNip()));
    html += "<br>";
    html += QString::fromStdString(customer.getAddress().getAddressTemplete());
    html +="</td></tr></table><table style='clear:both; border-style:none;'></table><table style=' margin: 1% 2% 0 2%; padding:2%; border: 2px solid black; width:90.5%; height:10%;'><tr><td>";
    html += "Payment data: <br>";
    html += QString::fromStdString(fvorder.getPaymentMethod());
    if(!fvorder.getPaymentMethodOption())
    {
         html += "<br> Account number: " + QString::fromStdString(owner.getAccountNumber());
         html += "<br> Title: " + QString::fromStdString(fvorder.getFVId());

    }

    html += "</td></tr></table><table style='border-style:none; margin: 1% 2% 0 2%; padding:2%; width:90.5%; height:30%;'><tr style='border-style:none;'><td style='border-style:none;'>";

    html += createTableHtmlString(fvorder);


    html += "</td></tr></table><table style='border-style:none; margin: 1% 2% 0 2%; padding:2%; width:90.5%; height:5%;'><tr><td>";
    html += "To pay: " + QString::number(fvorder.getSum()) +" zl <br> Payed: " + QString::number(fvorder.getSum())+ " zl";

    html += "</td></tr></table><table style='border-style:none; margin: 1% 2% 0 2%; padding:2%; width:90.5%; height:5%;'><tr style='border-style:none;'><td style='border-style:none;'><table style='border-style:none; float:left; width: 20%; height:100%; '><tr style='border-style:none;'><td style='border-style:none;'>";
    html += "<p align='center'>............................<br>podpis pracownika</p></td></tr></table><table style='border-style:none; float:left; width: 20%; height:100%; margin-left:50%; '><tr style='border-style:none;'><td style='border-style:none;'><p align='center'>............................<br>podpis klienta</p>";
    html += "</td></tr></table></td></tr></table></td></tr></table></body></html>";
    return html;
}


QString CreateFVDialog::createTableHtmlString(FVOrder fvorder)
{
    QString table;
    table = "<table width='100%'>";
    table += "<tr style='background-color:darkgray;' ><td>Nb.</td><td>Name</td><td>Um</td><td>Quantity</td><td>Price netto</td><td>Vat</td><td>Vat value</td><td>Price brutto</td></tr>";
    float vatRate =0, vatRateItems = 0;
    vector<itemsList> list = fvorder.getItemList();
    int size = list.size();

    for(int i = 0; i < size; i++)
    {
        vatRateItems = list[i].quantity * list[i].item.getVat()/(float)100 * list[i].item.getPrice();
        vatRate += vatRateItems;
        table += "<tr>";
        table += "<td>" + QString::number(i + 1) + "</td>";
        table += "<td>" + QString::fromStdString(list[i].item.getName()) + "</td>";
        table += "<td>" + QString::fromStdString(list[i].item.getQuantityType()) + "</td>";
        table += "<td>" + QString::number(list[i].quantity) + "</td>";
        table += "<td>" + QString::number(list[i].item.getPrice() * list[i].quantity - vatRateItems) + "</td>";
        table += "<td>" + QString::number(list[i].item.getVat()) + "</td>";
        table += "<td>" + QString::number(vatRateItems) + "</td>";
        table += "<td>" + QString::number(list[i].item.getPrice() * list[i].quantity) + "</td>";
        table += "</tr>";
    }

    table += "<tr style='background-color:darkgray;' ><td colspan='5'></td><td>Netto sum</td><td>Vat sum</td><td>Sum</td></tr>";

    table += "<tr><td colspan='5'></td><td>" + QString::number(fvorder.getSum() - vatRate) + "</td>";
    table += "<td>" + QString::number(vatRate) + "</td>";
    table += "<td>" + QString::number(fvorder.getSum()) + "</td>" + "</tr>";
    table += "</table>";
    return table;
}

vector<itemsList> CreateFVDialog::getItemsList()
{
    int rows = tableViewModel->rowCount();
    vector<itemsList> items;
    Database dbLoadItems("items.csv", 0);
    for(int i = 0; i < rows; i++)
    {
       int id = tableViewModel->data(tableViewModel->index(i, 0)).toInt();
       int quantity = tableViewModel->data(tableViewModel->index(i, 2)).toInt();
       Item item = dbLoadItems.getRecord<Item>(id);
       itemsList record = {item, quantity};
       items.push_back(record);
    }
    dbLoadItems.close();
    return items;
}

Customer CreateFVDialog::getCurrentCustomer(bool &selected)
{
    QModelIndexList indexes = ui->LstCustomers->selectionModel()->selectedRows();
    if(indexes.size() == 0)
    {
        selected = false;
        return Customer();
    }
    selected = true;
    QModelIndex index = indexes.at(0);
    int custId = index.row() + 1;
    Database dbLoadItems("customers.csv", 0);
    Customer currentCustomer = dbLoadItems.getRecord<Customer>(custId);
    dbLoadItems.close();
    return currentCustomer;
}


void CreateFVDialog::on_pushButton_2_clicked()
{
    close();
}


void CreateFVDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    QModelIndexList indexes =  ui->tableView->selectionModel()->selectedRows();
    int countRow = indexes.count();

    bool flagDif = false;
    for( int i = countRow; i > 1; i--)
        if (indexes.at(i-1).row()-1 != indexes.at(i-2).row())
           flagDif = true;

    if (!flagDif)
       tableViewModel->removeRows(indexes.at(0).row(),countRow,QModelIndex());
    else
       for( int i = countRow; i > 0; i--)
           tableViewModel->removeRow( indexes.at(i-1).row(), QModelIndex());
}

