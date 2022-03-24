#include "fvorder.h"


FVOrder::FVOrder(int customerId, string producentLogin, int paymentMethod, vector<itemsList> itemsLst, int discount = 0) : customerId(customerId), paymentMethodOption(paymentMethod), items(itemsLst), discount(discount)
{
    float sum = 0;

    for(char &znak : producentLogin)
        producentLoginId += (int)znak;


    for(itemsList &item : items)
        sum += item.item.getPrice() * item.quantity;

    this->date = QDate::currentDate();

    this->sum = sum;
    FVID = "FV_" + this->getDate()+ "_" + std::to_string(producentLoginId) + "_" + std::to_string(this->customerId) + "_" +  std::to_string( 5 + rand()%1000);
}

int FVOrder::getPaymentMethodOption() const
{
    return paymentMethodOption;
}

string FVOrder::getPaymentMethod() const
{
    return paymentMethod[paymentMethodOption];
}

float FVOrder::getSum() const
{
    return sum;
}

void FVOrder::setSum(float sum)
{
    this->sum = sum;
}

string FVOrder::getDate() const
{

   return date.toString("dd.MM.yyyy").toStdString();
}

vector<itemsList> FVOrder::getItemList() const
{
    return items;
}

int FVOrder::getDiscount() const
{
    return discount;
}

int FVOrder::getCustomerId() const
{
    return customerId;
}

int FVOrder::getProducentLoginId() const
{
    return producentLoginId;
}


string FVOrder::getFVId() const
{
    return FVID;
}

