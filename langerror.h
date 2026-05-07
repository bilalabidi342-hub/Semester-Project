#ifndef LANGERROR_H//we want to handle custom messages for error
#define LANGERROR_H

#include <iostream>
#include <cstring>
using namespace std;

class LangError{

    char message[200];//array storing error message

public:
    LangError(const char* msg)//when error is created it automatically runs
    {
        strcpy(message, msg);//copies this message
    }

    const char* getMessage()
    {
        return message;//to read the message
    }
};

#endif