#include "database.h"

Database::Database(string path, int mode, char delimiter)
{
    string newpath = "D:\\Qt\\projects\\FVGeneratorV2\\data\\" + path;
    if(mode == 0 )
        file.open(newpath, ios::in);
    else if(mode == 1)
        file.open(newpath, ios::in | ios::out);
    else if(mode == 2)
        file.open(newpath, ios::app);
    else if(mode == 3)
        file.open(newpath, ios::out | ios::trunc);

    this->delimiter = delimiter;
}

Database::~Database()
{
    if(!file.is_open())
        file.close();
}

void Database::close()
{
     file.close();
}

bool Database::saveData(vector<string> toSaveLine)
{
    if(!file.good())
        return false;
    string line;
    for(int i = 0; i < toSaveLine.size(); i++)
    {
         line += toSaveLine[i] + delimiter;
    }
    line[line.length()-1] = '\n';

    file << line;
    return true;
}

/**
 *Funciton modify row of data
 *@param lineNumber number of line in file
*/
void Database::modifyRow(int lineNumber, vector<string> toSaveLine)
{
    file.clear();
    file.seekg(0, ios::beg);
    if(!file.good())
        return;
    int i = 0;
    string line, tempLine, fileContent;
    for(int i = 0; i < toSaveLine.size(); i++)
    {
         line += toSaveLine[i] + delimiter;
    }
    line[line.length()-1] = '\n';


    while(getline(file, tempLine))
    {
        i++;
        if(i == lineNumber)
        {
            fileContent += line;
            continue;
        }
        fileContent += tempLine + '\n';
    }

    file.clear();
    file.seekg(0, ios::beg);

    file << fileContent;

}




void Database::initLastId()
{
    if(!file.good())
        return;
    vector<string> conversion;
    int pos = 0;
    string line;
    getline(file, line);
    string temp;
    while ((pos = line.find(delimiter)) != string::npos) {
        temp = line.substr(0, pos);
        conversion.push_back(temp);
        line.erase(0, pos + 1);
    }
    conversion.push_back(line);
    LastId::Init(conversion);
    conversion.clear();
    conversion.shrink_to_fit();
}
