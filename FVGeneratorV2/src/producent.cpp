#include "producent.h"


Producent::Producent(vector<string> data)
{
    int size = data.size();


    if(!(size == 9 || size == 8 || size == 7))
    {
        string message = "Bad data";
        throw LoadingException(message.data());
    }


    login = data[0];
    name = data[1];
    adres = Address(data[2]);
    try
    {
       nip = std::stoi(data[3]);
    }
    catch(std::exception const & e)
    {
         qCritical() <<"error : " << e.what();
    }
    email = data[4];
    phone = data[5];
    accountNumber = data[6];

    if(size >= 8)
        webPage = data[7];
    if(size >= 9)
        fax = data[8];
}

void Producent::setLogin(string login)
{
    this->login = login;
}
/**
 * Function set email of producent with validation
 * @brief set email
 * @param email - email to set in bad format not set an email
*/
void Producent::setEmail(string email)
{
    if(email.find('@') != string::npos)
        return;
    this->email = email;
}

void Producent::setWebPage(string webPage){
    this->webPage = webPage;
}

void Producent::setFax(string fax)
{
    this->fax = fax;
}


void Producent::setPhone(string phone)
{
    this->phone = phone;
}

string Producent::getLogin() const
{
    return login;
}

string Producent::getEmail() const
{
    return email;
}

string Producent::getPhone() const
{
    return phone;
}

string Producent::getFax() const
{
    return fax;
}

string Producent::getWebPage() const
{
    return webPage;
}

string Producent::getAccountNumber() const
{
    return accountNumber;
}
