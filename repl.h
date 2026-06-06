// REPL.h
// Read Evaluate Print Loop
// Runs the language interactively or from a file
// Connects Lexer + Parser + Interpreter together
#ifndef REPL_H //taking input and printing results and repeat the process
#define REPL_H

#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "LangError.h"
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

class REPL
{
private:
    Interpreter interpreter;//obj of interpreter

public:

    void runLine(const char* source)//runs one line
    {
        try//first it tries and if code is risky it goes to cstch
        {
            Lexer lexer(source);
            lexer.tokenize();//converts line to tokens
            

            Parser parser(lexer.tokens, lexer.getTokenCount());//returns count
            ASTnode* tree = parser.parse();//assigning values by node logic

            interpreter.run(tree);//run that tree
        }
        catch (LangError& e)//catch prints the error message(if any error found that we declared)
        {
            cout << e.getMessage() << endl;
        }
    }

    void runInteractive()
    {   
        cout << "==========================================\n";
        cout << "  Welcome to - Apni Programming Language  \n";
        cout << "==========================================\n";
        cout << "for any type of help: type 'madad' \n";
        cout << "To exit: type 'khatam' \n\n";

        char input[1000];//the input memory

        while (true)
        {
            cout << ">> " << flush;//forces to print it

            cin.getline(input, 1000);//gets (our string code)

            if (strcmp(input, "khatam") == 0)
            {
                cout << " Khuda Hafiz " << endl;
                break;
            }

            if (input[0] == '\0')//skip empty inputs
                continue;

            if (strcmp(input, "madad") == 0)
            {
                cout << "  Commands:\n";
                cout << "  ================\n";
                cout << "  dikhao [value]\n";
                cout << "  x = [expression]\n";
                cout << "  agar [cond] { }\n";
                cout << "  jabtak [cond] { }\n";
                cout << "  khatam\n";
                cout << "  ================\n";
                continue;
            }

            runLine(input);//follows all the files and their functionalities
        }
    }

    void runFile(const char* filename)
    {
        FILE* file = fopen(filename, "r");

        if (file == nullptr)
        {
            throw LangError("ERROR: file was not found ");
        }

        char source[5000];
        int i = 0;
        char c;

        while ((c = fgetc(file)) != EOF && i < 4999)
        {
            source[i++] = c;
        }

        source[i] = '\0';

        fclose(file);

        runLine(source);
    }
    void runMultiLine()
{
    cout << "==========================================\n";
    cout << "  Welcome to - Apni Programming Language  \n";
    cout << "==========================================\n";
    cout << "Apna poora code likhein.\n";
    cout << "'chalao' likh ke code run karein.\n";
    cout << "'khatam' likh ke band karein.\n\n";

    char fullCode[5000];   // stores the whole program
    fullCode[0] = '\0';    // start empty

    char input[1000];      // one line at a time

    while (true)
    {
        cout << "... " << flush;   // ... shows you are still writing

        cin.getline(input, 1000);

        // exit completely
        if (strcmp(input, "khatam") == 0)
        {
            cout << "Khuda Hafiz!" << endl;
            break;
        }

        // run everything typed so far
        if (strcmp(input, "chalao") == 0)
        {
            cout << "\n==========================================\n";
            cout << "OUTPUT:\n";
            cout << "==========================================\n";

            runLine(fullCode);   // run the whole collected code

            cout << "==========================================\n\n";

            // clear the code buffer for next program
            fullCode[0] = '\0';
            continue;
        }

        // add this line to the full code with a space separator
        strcat(fullCode, input);
        strcat(fullCode, " ");  // space acts as line separator for Lexer
    }
}
};

#endif