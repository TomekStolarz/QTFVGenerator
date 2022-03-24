#ifndef LOADINGEXCEPTION_H
#define LOADINGEXCEPTION_H

#include <exception>

using namespace std;

class LoadingException: public exception {
private:
    char *exceptionText;

public:
    LoadingException(char * exceptionText): exceptionText(exceptionText) {}

    virtual const char* what() const throw(){
        return exceptionText;
    }
};

#endif // LOADINGEXCEPTION_H
