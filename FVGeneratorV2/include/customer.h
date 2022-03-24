#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include "address.h"
#include "person.h"
#include <vector>
#include <QApplication>
#include "lastid.h"
#include "database.h"
#include "loadingException.h"

using namespace std;

class Customer : public Person
{
private:
    int id;
    int typ;//0 - company, 1 - priviate
    string lastName;
    /**
     * initializing and saving data to customer file
    */
    void init();
public:
    Customer(){};
    Customer(vector<string> data);
    Customer(int typ, string name, string lastName, Address adres);
    Customer(int typ, string name, Address adres, long nip);


    /**
     * @brief getType
     * @return type of cutomer 0- company, 1- private
     */
    int getType() const;

    /**
     * @brief getLastName
     * funcion return last name of private customer (type 1) for company customer do nothing
     * @return last name of private customer
     */
    string getLastName() const;

    /**
    * setting lastname of customer only customer which have type - 1 for type 0 function do nothing
    * @param lastName last name to set
    */
    void setLastName(string lastName);

    /**
     * Fucntion returning id of customer
     * @brief getId
     * @return id of customer
    */
    int getId() const;

    vector<string> toSaveData();

};

#endif // CUSTOMER_H
