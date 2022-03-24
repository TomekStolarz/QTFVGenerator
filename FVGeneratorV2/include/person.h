#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include "address.h"

using namespace std;

class Person
{
protected:
    string name;
    Address adres = Address();
    long nip;
public:
    Person(){};
    Person(string name, Address adres, long nip): name(name), adres(adres), nip(nip){};
    Person(string name, Address adres): name(name), adres(adres){};
    /**
     * @brief getName
     * @return Name of cutomer: firstname or company name
     */
    string getName() const;

    /**
     * @brief getAddress
     * funciton retruning address of customer
     * @return address of customer
    */
    Address getAddress() const;

    long getNip() const;
    /**
    * setting name of customer
    * @param name name which you want to set
    */
    void setName(string name);

    /**
    * setting adres of customer
    * @param adres adres to set
    */
    void setAddress(Address adres);
};

#endif // PERSON_H
