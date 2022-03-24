#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <vector>
#include <string>
#include "lastid.h"
#include "database.h"
#include <QApplication>
#include "loadingException.h"

using namespace std;

class Item
{
private:
    int id;
    string name;
    float price;
    int vat;
    string quantityType = "pcs";
    /**
     * initializing and saving data to customer file
    */
    void init();
public:
    Item(){};
    Item(vector<string> data);
    Item(string name, float price, int vat, string quantityType);
    Item(string name, float price, int vat);

    /**
     * Fucntion returning vat value without % sign in integer value
     * @brief getVat
     * @return value of vat
    */
     int getVat() const;
    /**
     * Fucntion returning brutto price of item
     * @brief getPrice
     * @return price of item
    */
     float getPrice() const;
    /**
     * Fucntion returning quanttity type of item standard value is pcs
     * @brief getQuantityType
     * @return quantity type of item
    */
     string getQuantityType() const;
    /**
     * Fucntion returning name of item
     * @brief getName
     * @return name of item
    */
    string getName() const;
    /**
     * Fucntion returning id of item
     * @brief getId
     * @return id of item
    */
    int getId() const;

    /**
     *Function setting vat value of item
     *@brief setVat
     *@param vat vat value in integer format
    */
    void setVat(int vat);
    /**
     *Function setting brutto price of item
     *@brief setPrice
     *@param price price to be setting rounding to 2 place after dot
    */
    void setPrice(float price);
    /**
     *Function setting name of item
     *@brief setName
     *@param name name to be setting
    */
    void setName(string name);
};

#endif // ITEM_H
