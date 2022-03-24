#ifndef ADRESS_H
#define ADRESS_H
#include <iostream>
#include <string>
#include <vector>
#include <QApplication>


using namespace std;

class Address
{
private:
    string street;
    int number;
    string city;
    int zipCode;
    string country;
public:
    Address(){};
    Address(string dataFromFile);
    Address(string street,  int number, string city, int zipCode, string country) : street(street), number(number), city(city), zipCode(zipCode), country(country){};
    /**
     * Function returning data to easy display in format like on letter to marking someone address
    * @return adress templete in post code format
    */
    string getAddressTemplete() const;
    /**
    * setting city of address
    * @param city name of city
    */
    void setCity(string city);
    /**
    * setting zip code of address
    * @param zipCode zip code in formal XXXXX where X is integer numeber
    */
    void setZipCode(int zipCode);
    /**
    * setting street of address
    * @param steet name of street
    */
    void setStreet(string street);
    /**
    * setting country of address
    * @param country name of country
    */
    void setCountry(string country);
    /**
    * setting number of home of address
    * @param number integer value without  any letters
    */
    void setNumber(int number);

    string getAddressSaveFormat() const;
};

#endif // ADRESS_H
