#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "lastid.h"
#include <QApplication>


using namespace std;

class Database
{
private:
    fstream file;
    char delimiter;
    vector<string> headers;
public:
    /**
     * Konstruktor
     * @param path path to the file
     * @param mode mode of open file 0- reading, 1-writing, 2- append, 3- rewrting
     * @param delimiter delimiter of data default = ,
    */
    Database(string path, int mode, char delimiter = ',');
    ~Database();


    /**
     * Function save data to the file database
     * @param toSaveLine data to save in split line in table
     * @return true when data was saved
    */
    bool saveData(vector<string> toSaveLine);

    /**
     *Funciton modify row of data
     *@param lineNumber number of line in file
     *@param toSaveLine data to save in split line in table
    */
    void modifyRow(int lineNumber, vector<string> toSaveLine);

    /**
     *Fucntion getting data from file to vector
     *@param amount amount of data
     *@return vector with data
    */    
    template <typename T>
    vector<T> getRecords(int amount);

    /**
     *Fucntion getting one record from file from specified line
     *@param lineNumber number of line
     *@return t element
    */
    template <typename T>
    T getRecord(int lineNumber);


    /**
     *Fucntion getting all data from file to vector
     *@return vector with data
    */
    template <typename T>
    vector<T> getRecords();

    /**
     * Function converting string to T class object
     * @param line string to conversion
     * @return T object
    */
    template <typename T>
    T getRecord(string line);

    /**
     * funcition initializing lastId data class
    */
    void initLastId();
    /**
     * closing file
    */
    void close();
};

template <typename T>
vector<T> Database::getRecords(int amount)
{
    int i = 0;

    vector<T> data;
    string line;
    while(i++ < amount)
    {
      getline(file, line);
      if(line.empty())
          break;
      T record = getRecord<T>(line);
      data.push_back(record);
    }
    return data;
}


template <typename T>
vector<T> Database::getRecords()
{
    file.clear();
    file.seekg(0);
    if(!file.good())
        return {};
    vector<T> data;
    string line;
    while(getline(file, line))
    {
        T record = getRecord<T>(line);
        data.push_back(record);
    }
    return data;
}

template <typename T>
T Database::getRecord(int lineNumber)
{
    file.clear();
    file.seekg(0);
    string line;
    for(int i=0; i<lineNumber; i++)
        getline(file, line);
    T record = getRecord<T>(line);
    return record;
}

template <typename T>
T Database::getRecord(string line)
{
    vector<string> conversion;
    int pos = 0;
    string temp;
    while ((pos = line.find(delimiter)) != string::npos) {
        temp = line.substr(0, pos);
        conversion.push_back(temp);
        line.erase(0, pos + 1);
    }
    conversion.push_back(line);
    T rec;
    try {
         T record(conversion);
         rec = record;
    }
    catch (exception ex) {
        qDebug() << ex.what() <<"\n";
    }

    conversion.clear();
    conversion.shrink_to_fit();
    return rec;
}

#endif // DATABASE_H
