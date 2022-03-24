#ifndef FVORDER_H
#define FVORDER_H

#include <iostream>
#include "item.h"
#include <vector>
#include <QDateTime>
using namespace std;

struct itemsList
{
    Item item;
    int quantity;
    bool operator>(const itemsList &rhs)const
    {
        if(item.getPrice() * quantity > rhs.item.getPrice() * rhs.quantity)
            return true;
        return false;
    }

    bool operator<( const itemsList &rhs)const
    {
        if(item.getPrice() * quantity < rhs.item.getPrice() * rhs.quantity)
            return true;
        return false;
    }
};


class FVOrder
{
private:
    string FVID;
    int customerId;
    int producentLoginId = 0;
    string paymentMethod[2]={"online transfer", "cash"};
    int paymentMethodOption;
    vector<itemsList> items;
    int discount;
    float sum;
    QDate date;
public:
    FVOrder(int customerId, string producentLogin, int paymentMethod, vector<itemsList> itemsList, int discount );

    /**
     *Function return method of payment
     *@brief getPaymentMethod
     *@return method of payment
    */
    string getPaymentMethod() const;
    /**
     *Function return index method of payment
     *@brief getPaymentMethodOption
     *@return index method of payment
    */
    int getPaymentMethodOption() const;
    /**
     *Function return order price
     *@brief getSum
     *@return order price
    */
    float getSum() const;
    /**
     *Function setting order price
     *@brief setSum
     *@param sum order price
    */
    void setSum(float sum);
    /**
     *Fucntion converting and return date in string format
     *@brief getDate
     *@return date in string format DD.MM.YYYY
    */
    string getDate() const;
    /**
     *Function retruning items list from order
     *@brief getItemList
     *@return item list in vector
    */
    vector<itemsList> getItemList() const;
    /**
     *fucntion return discount value
     *@brief getDiscount
     *@param discount value
    */
    int getDiscount() const;
    /**
     *fucntion return id of customer order
     *@brief getCustomerId
     *@return customer id
    */
    int getCustomerId() const;
    /**
     *fucntion return id of produecnt order
     *@brief getProducentId
     *@return  producent login order
    */
    int getProducentLoginId() const;
    /**
     *fucntion return id of fv
     *@brief getFVId
     *@return  fv id
    */
    string getFVId() const;
    /**
     * Comparing two itemsList item (total price)
     * @return true if first item is bigger
    */

};

#endif // FVORDER_H
