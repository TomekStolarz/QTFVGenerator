#include "item.h"

Item::Item(vector<string> data)
{
    string quantityType = "pcs";

    if(data.size() != 5)
    {
        string message = "Bad data";
        throw LoadingException(message.data());
    }



    try
    {
        id = std::stoi(data[0]);
        price = stof(data[2]);
        vat = std::stoi(data[3]);
    }
    catch(std::exception const & e)
    {
         qCritical() <<"error : " << e.what();
    }
    name = data[1];
    quantityType = data[4];
}

Item::Item( string name, float price, int vat, string quantityType) :  name(name), price(price) , vat(vat), quantityType(quantityType)
{
    init();
};

Item::Item( string name, float price, int vat) : name(name), price(price) , vat(vat)
{
    init();
};

void Item::init()
{
    LastId::increamentItemLastId();
    id = LastId::getItemLastId();
    Database itemSaving("items.csv", 2);
    vector<string> toSave;

    toSave.push_back(std::to_string(id));
    toSave.push_back(name);
    toSave.push_back(std::to_string(price));
    toSave.push_back(std::to_string(vat));
    toSave.push_back(quantityType);

    itemSaving.saveData(toSave);
    itemSaving.close();
    toSave.clear();
    toSave.shrink_to_fit();

}

int Item::getVat() const
{
    return vat;
}

float Item::getPrice() const
{
    return price;
}

string Item::getQuantityType() const
{
    return quantityType;
}

string Item::getName() const
{
    return name;
}

int Item::getId() const
{
    return id;
}


void Item::setVat(int vat)
{
    this->vat = vat;
}

void Item::setPrice(float price)
{
    this->price = price;
}


void Item::setName(string name)
{
    this->name = name;
}
