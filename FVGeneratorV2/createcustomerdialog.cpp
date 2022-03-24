#include "createcustomerdialog.h"
#include "ui_createcustomerdialog.h"



CreateCustomerDialog::CreateCustomerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateCustomerDialog)
{
    ui->setupUi(this);
}

CreateCustomerDialog::~CreateCustomerDialog()
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



void CreateCustomerDialog::on_BtnAdd_clicked()
{
    int cnt = 0;
    bool exit = false;
    QRegularExpression nameToFind("CstLbl");
    QList<QLineEdit*> lineEdits = this->findChildren<QLineEdit*>(nameToFind);
    for(QLineEdit *lineEdit : lineEdits)
        if(lineEdit->text().isEmpty())
           {
            cnt++;
           }
    if(cnt > 1 || lineEdits.size() == 0)
    {
         ui->label_error->setText("Fill the form");
         return;
    }


    nameToFind.setPattern("AdrLbl");
    lineEdits = this->findChildren<QLineEdit*>(nameToFind);
    for(QLineEdit *lineEdit : lineEdits)
        if(lineEdit->text().isEmpty())
           {
            exit = true;
            break;
           }
    if(exit)
    {
         ui->label_error->setText("Fill the form");
         return;
    }

    bool state = ui->chxCompany->isChecked();
    Address adres(ui->AdrLblStreet->text().toStdString(), std::stoi(ui->AdrLblNumber->text().toStdString()),
                  ui->AdrLblCity->text().toStdString(), std::stoi(ui->AdrLblZipCode->text().toStdString()),
                  ui->AdrLblCounty->text().toStdString());
    if(state)
    {
        Customer newCustomer(int(!state), ui->CstLblname->text().toStdString(), adres, std::stol(ui->CstLblNip->text().toStdString()));

    }
    else
    {
        Customer newCustomer(int(!state), ui->CstLblname->text().toStdString(), ui->CstLblLastName->text().toStdString(), adres );
    }


    close();
}


void CreateCustomerDialog::on_chxCompany_stateChanged(int arg1)
{
    bool state = ui->chxCompany->isChecked();

    ui->CstLblLastName->setReadOnly(state);
    ui->CstLblNip->setReadOnly(!state);
    ui->CstLblLastName->clear();
    ui->CstLblNip->clear();
}

