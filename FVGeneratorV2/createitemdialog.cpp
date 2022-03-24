#include "createitemdialog.h"
#include "ui_createitemdialog.h"

CreateItemDialog::CreateItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateItemDialog)
{
    ui->setupUi(this);
}

CreateItemDialog::~CreateItemDialog()
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


void CreateItemDialog::on_BtnAdd_clicked()
{
    bool exit = false;
    const QList<QLineEdit*> lineEdits = this->findChildren<QLineEdit*>();
    for(QLineEdit *lineEdit : lineEdits)
        if(lineEdit->text().isEmpty())
           {
            exit = true;
            break;
           }
    if(lineEdits.size() == 0)
        exit = true;

    if(exit)
    {
         ui->label_6->setText("Fill the form");
         return;
    }

    Item newItem(ui->LblName->text().toStdString(), std::stof(ui->LblPrice->text().toStdString()),
                 std::stoi(ui->LblVatRate->text().toStdString()), ui->LblQuantityType->text().toStdString());

    close();
}

