#include "customer.h"

Customer::Customer(vector<string> data)
{

    if(data.size() != 5)
    {
        string message = "Bad data";
        throw LoadingException(message.data());
    }

    try
    {
        id = std::stoi(data[0]);
        typ = std::stoi(data[1]);
        if(!typ)
            nip = std::stoi(data[4]);
        else
            lastName = data[4];
    }
    catch(std::exception const & e)
    {
         qCritical() <<"error : " << e.what();
    }
    name = data[2];
    adres = Address(data[3]);

}

Customer::Customer(int typ, string name, string lastName, Address adres) :Person(name, adres), typ(typ), lastName(lastName){
    init();
};

Customer::Customer(int typ, string name, Address adres, long nip): Person(name, adres, nip),  typ(typ){
    init();
};

void Customer::init()
{
    LastId::increamentCustomerLastId();
    id = LastId::getCustomerLastId();
    Database customerSaving("customers.csv", 2);
    vector<string> toSave = toSaveData();
    customerSaving.saveData(toSave);
    customerSaving.close();
    toSave.clear();
    toSave.shrink_to_fit();

}

int Customer::getType() const
{
    return typ;
}

string Customer::getLastName() const
{
    return lastName;
}

void Customer::setLastName(string lastName)
{
    this->lastName = lastName;
}

int Customer::getId() const
{
    return id;
}

 vector<string> Customer::toSaveData()
 {
     vector<string> saveFormat;

     saveFormat.push_back(std::to_string(id));
     saveFormat.push_back(std::to_string(typ));
     saveFormat.push_back(name);
     saveFormat.push_back(adres.getAddressSaveFormat());
     if(!typ)
         saveFormat.push_back(std::to_string(nip));
     else
         saveFormat.push_back(lastName);

     return saveFormat;
 }
