#include "mainwindow.h"
#include "producent.h"
#include "database.h"
#include <QApplication>

Producent owner;
using namespace std;

void loadLastId();
void help();
void addProducent();
string getAddress();
bool isNumber(const string& str);

int main(int argc, char *argv[])
{
    bool isGood = false;
    srand(time(NULL));
    string commandList[] = {"add", "normal"};
    if(!(argc == 2 || argc == 3))
    {
        help();
        return 0;
    }

    string command = argv[1];

    for(int i= 0; i < 2; i++)
    {
        if(command == commandList[i])
        {
            isGood = true;
            break;
        }
    }

    if(!isGood)
    {
        help();
        return 0;
    }

    isGood = false;

    if(argc == 2 && command == commandList[0] )
    {
        addProducent();
        return 0;
    }
    else if(command == commandList[1] && argc == 3)
    {
        string log = argv[2];
        Database producentFetch("../data/producenci.csv", 0);
        vector<Producent> allProducents = producentFetch.getRecords<Producent>();
        producentFetch.close();

        for(Producent &producent : allProducents)
        {
            if(producent.getLogin() == log)
            {
                owner = producent;
                isGood = true;
                break;
            }
        }
        allProducents.clear();
        allProducents.shrink_to_fit();

        if(!isGood)
        {
            cout << "bad login\n";
            help();
            return 0;
        }
    }
    else
    {
        help();
        return 0;
    }

    loadLastId();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}



void loadLastId()
{
    Database lastIdStream("lastid.csv", 0);
    lastIdStream.initLastId();
    lastIdStream.close();
}

void help()
{
    cout << "----------FVGenerator Progam----------------" <<endl;
    cout << "Help " <<endl;
    cout << "To run this program use one of tree parameter after space: \n";
    cout << "add - in this mode you can add a producent of fv\n";
    cout << "normal [login] - start the program in normal mode. You must type a login \n";
    cout << "help - how to use a program \n";
}

bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

string getAddress()
{
    string adresString, temp;
    string names[] = {"street", "number", "city", " zipCode without - sign", "country"};


    for(int i = 0; i < 5; i++)
    {
        cout << "Type a "<< names[i] <<": ";
        cin >> temp;
        if(i == 1 || i == 3)
        {
            while(isNumber(temp) == 0)
            {
                cout << "Bad value. Write correct: ";
                cin >> temp;
            }
        }

        if(i != 4)
            adresString += temp + ";";
    }
    adresString += temp;

    return adresString;
}

void addProducent()
{
    vector<string> toSaveData;
    string temp;
    bool endCase = false;
    string names[] = {"login", "name of producent", "adres", "nip", "email", "phone", "accountNumber"};

    for(int i = 0; i < 7; i++)
    {
        if(i == 2)
        {
            cout << "Type a "<< names[i] <<"\n";
            temp = getAddress();
            toSaveData.push_back(temp);
            continue;
        }
        cout << "Type a "<< names[i] <<": ";
        cin >> temp;
        if(i == 3)
        {
            while(isNumber(temp) == 0)
            {
                cout << "Bad value. Write correct: ";
                cin >> temp;
            }
        }
        toSaveData.push_back(temp);
    }


    cout << "Typa a webPage if you want( if not type 0): ";
    cin >> temp;
    try
    {
        if(std::stoi(temp) == 0)
            endCase = true;
    }
    catch(std::exception const & e)
    {
    }

    if(!endCase)
    {
        toSaveData.push_back(temp);

        cout << "Typa a fax if you want( if not type 0): ";
        cin >> temp;
        try{
            if(std::stoi(temp) == 0)
                endCase = true;
        }
        catch(std::exception const & e)
        {
        }
        if(!endCase)
            toSaveData.push_back(temp);
    }

    Database producentSaving("../data/producenci.csv", 2);
    if(producentSaving.saveData(toSaveData))
        cout<< "Zapisano dane!\n";
    else
        cout<< "Nie udalo sie dodac producenta\n";

    toSaveData.clear();
    toSaveData.shrink_to_fit();

    producentSaving.close();
}
