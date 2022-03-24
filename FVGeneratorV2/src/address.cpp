#include "address.h"

Address::Address(string dataFromFile)
{
    vector<string> conversion;
    int pos = 0;
    string temp;
    while ((pos = dataFromFile.find(';')) != string::npos) {
        temp = dataFromFile.substr(0, pos);
        conversion.push_back(temp);
        dataFromFile.erase(0, pos + 1);
    }
    conversion.push_back(dataFromFile);

    if(conversion.size() != 5)
    {
        conversion.clear();
        conversion.shrink_to_fit();
        this->~Address();
    }

    street = conversion[0];
    try
    {
        number = std::stoi(conversion[1]);
        zipCode = std::stoi(conversion[3]);
    }
    catch(std::exception const & e)
    {
         qCritical() <<"error : " << e.what();
    }
    city = conversion[2];
    country = conversion[4];

    conversion.clear();
    conversion.shrink_to_fit();
}

string Address::getAddressTemplete() const
{
    string adresTemplate = street;
    adresTemplate += " " + to_string(number) + "<br>";
    adresTemplate += to_string(zipCode) + " " + city + ", " + country + "<br>";

    return adresTemplate;
}

void Address::setCity(string city)
{
    this->city = city;
}

void Address::setZipCode(int zipCode)
{
    this->zipCode = zipCode;
}

void Address::setStreet(string street)
{
    this->street = street;
}

void Address::setCountry(string country)
{
    this->country = country;
}
/**
* setting number of home of address
* @param number integer value without  any letters
*/
void Address::setNumber(int number)
{
    this->number = number;
}


string Address::getAddressSaveFormat() const
{
    string format;

    format = street +";" + std::to_string(number) + ";" + city + ";" + std::to_string(zipCode) + ";" + country;

    return format;
}
