#ifndef PRODUCENT_H
#define PRODUCENT_H
#include "person.h"
#include <vector>
#include "loadingException.h"

class Producent : public Person
{
private:
    string login;
    string email;
    string phone;
    string accountNumber;
    string webPage;
    string fax;
public:
    Producent(){};
    Producent(vector<string> data);
    Producent(string login, string name, Address adres, long nip, string email, string phone, string accountNumber, string webPage, string fax) : Person(name, adres, nip), login(login), email(email), phone(phone), accountNumber(accountNumber), webPage(webPage),fax(fax) {};
    Producent(string login, string name, Address adres, long nip, string email, string phone, string accountNumber, string webPage) : Person(name, adres, nip), login(login), email(email), phone(phone), accountNumber(accountNumber), webPage(webPage) {};
    Producent(string login, string name, Address adres, long nip, string email, string phone, string accountNumber) : Person(name, adres, nip),login(login), email(email), phone(phone),accountNumber(accountNumber) {};

    /**
     * Function set login of producent
     * @brief setLogin
     * @param login - login to set
    */
    void setLogin(string login);
    /**
     * Function set email of producent with validation
     * @brief set email
     * @param email - email to set in bad format not set an email
    */
    void setEmail(string email);
    /**
     * Function set web page adres of producent
     * @brief setWebPage
     * @param webPage - webPage to set
    */
    void setWebPage(string webPage);
    /**
     * Function set fax number of producent
     * @brief setFax
     * @param fax - fax to set
    */
    void setFax(string fax);
    /**
     * Function set phone number of producent
     * @brief setPhone
     * @param phone - phone to set with prefix country code
    */
    void setPhone(string phone);

    /**
     * function return login of producent
     * @brief getLogin
     * @return login in string format
    */
    string getLogin() const;
    /**
     * function return email of producent
     * @brief getEmail
     * @return email in string format
    */
    string getEmail() const;
    /**
     * function return phone number of producent
     * @brief getPhone
     * @return  phone number  in string format with prefix of country
    */
    string getPhone() const;
    /**
     * function return fax number of producent
     * @brief getFax
     * @return fax number in string format
    */
    string getFax() const;
    /**
     * function return web page address of producent
     * @brief getWebPage
     * @return web page address in string format
    */
    string getWebPage() const;
    /**
     * function return account number of producent
     * @brief getAccountNumber
     * @return account numbe in string format
    */
    string getAccountNumber() const;
};

#endif // PRODUCENT_H
