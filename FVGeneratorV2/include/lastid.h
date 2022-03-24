#ifndef LASTID_H
#define LASTID_H

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class LastId
{
private:
    static int customerLastId;
    static int itemLastId;
    static bool isSaved;
public:
    static void Init(vector<string> data);

    /**
     * Function increamenting lastid of customer
    */
    static void increamentCustomerLastId();

    /**
     * Function increamenting lastid of item
    */
    static void increamentItemLastId();
    /**
     * Function returning value of customer last id
    */
    static int getCustomerLastId();

    /**
     * Function returning value of item last id
    */
    static int getItemLastId();
    /**
     * Function returning  information about changing variable
    */
    static bool getIsSaved();

};



#endif // LASTID_H
