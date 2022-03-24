#include <lastid.h>
 void LastId::Init(vector<string> data)
{
    customerLastId = atoi(data[0].c_str());
    itemLastId = atoi(data[1].c_str());
}


 void LastId::increamentCustomerLastId()
{
    customerLastId++;
    isSaved = false;
}



 void LastId::increamentItemLastId()
{
    itemLastId++;
    isSaved = false;
}

 int LastId::getCustomerLastId()
{
    return customerLastId;
}

 int LastId::getItemLastId()
{
    return itemLastId;
}

 bool LastId::getIsSaved()
 {
     return isSaved;
 }

int LastId::customerLastId = 0;
int LastId::itemLastId = 0;
bool LastId::isSaved = true;
