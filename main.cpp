#include "REPL.h"
#include "LangError.h"
#include <iostream>

using namespace std;

int main()
{
    try
    {
        REPL Repl;
        Repl.runMultiLine();
    }
    catch (LangError& e)
    {
        cout << "[!] " << e.getMessage() << endl;
    }

    return 0;
}