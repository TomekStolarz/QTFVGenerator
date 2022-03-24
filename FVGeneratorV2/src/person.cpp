#include "person.h"

string Person::getName() const
{
    return name;
}


Address Person::getAddress() const
{
    return adres;
}

long Person::getNip() const
{
    return nip;
}

void Person::setName(string name)
{
    this->name = name;
}

void Person::setAddress(Address adres)
{
    this->adres = adres;
}
