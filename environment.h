// Environment.h
// Stores variable names and their values
// Works like a notebook during program execution
// Example: set("x", 10) stores x=10, get("x") returns 10
#ifndef ENVIRONMENT_H//the file that stores mainly the variables and their values
#define ENVIRONMENT_H
#include <iostream>
#include <cstring>
#include "LangError.h"
using namespace std;
#define MAX_VARS 50//since we dont use vectors so we manually define it
class Environment{
private:
    //each bigger array stores a string
    char names[MAX_VARS][50];//now the bigger array stores the var name and (50) the name alphabets to read the var name
    float values[MAX_VARS];//this array stores the the value at the variables
    int count;//tells how many variables are stored yet

public:
Environment()
{
    count = 0;//since no variables yet
}
void set(const char* name, float val)//store variable name with value
{
    // Check if variable already exists
    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], name) == 0)//compares that if it already exists or not
        {
            // if Variable found update its value
            values[i] = val;
            return;
        }
    }

    //If not found create a new variable
    strcpy(names[count], name);
    values[count] = val;//store the valuw at the same index
     if (count >= MAX_VARS)
      throw LangError("Language can't handle that much variables ");
    count++;
}
float get(const char* name)//to actually get the varuable
{
    // search all variables
    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], name) == 0)
        {
            // Found return its value
            return values[i];
        }
    }

    char msg[200];//temp storage for err message
    strcpy(msg, "ERROR: variable '");//when error mesg occur
    strcat(msg, name);//build message
    strcat(msg, "' not found");

    throw LangError(msg);//stop fun and skip everything
}

};
#endif