#ifndef LEXER_H//done so a copy created causes us no problem 
#define LEXER_H

#include "Token.h"//the token library
#include <cstring>
#include <cctype>
#include "LangError.h"

#define MAX_TOKENS 200//constant tokens defined

class Lexer//code scanner
{
private:
    char source[1000];//the string that we give it as a code
    int pos; //position every string
    int tokenCount;

public:
    Token tokens[MAX_TOKENS];

    Lexer(const char* src)
    {
        strcpy(source, src);//copies the source code in src
        pos = 0;
        tokenCount = 0;
    }

    void addToken(TokenType type, const char* text)
    {
        // prevent overflow of token array(since we set tokens)
        if (tokenCount >= MAX_TOKENS - 1)
            throw LangError("The program is very long for this");

        tokens[tokenCount].type = type;
        strcpy(tokens[tokenCount].value, text);
        tokenCount++;
    }

    void tokenize()
{
    // empty input handling
    if (source[0] == '\0')//it handles if the input is totally empty
    {
        addToken(END, "END");
        return;//it doent run this tokenize and return
    }

    while (source[pos] != '\0')
    {
        // Skip spaces
    if (source[pos] == ' ' || source[pos] == '\n' || source[pos] == '\t' || source[pos] == '\r'){
      
              pos++;
              continue;
}

        // handle the == logic
        if (source[pos] == '=' && source[pos + 1] == '=')
        {
            addToken(EQEQ, "==");
            pos += 2;//it moves two spaces
            continue;
        }

        if (isdigit(source[pos]))//checks if it is a number
        {
            char num[50];
            int i = 0;

            while (isdigit(source[pos]))
            {
                num[i] = source[pos];
                i++;
                pos++;
            }

            num[i] = '\0';
            addToken(NUMBER, num);
            continue;
        }

        // Identifiers for letters mainly for our print function
        if (isalpha(source[pos]))
        {
            char word[50];
            int i = 0;

            while (isalpha(source[pos]))
            {
                word[i] = source[pos];
                i++;
                pos++;
            }

            word[i] = '\0';

            if (strcmp(word, "dikhao") == 0)//for our print
                addToken(PRINT, word);

            else if (strcmp(word, "agar") == 0)//for the if statement
                addToken(AGAR, word);

            else if (strcmp(word, "warna") == 0)//for else satemnts
                addToken(WARNA, word);

            else if (strcmp(word, "jabtak") == 0)//for our loop 
                addToken(JABTAK, word);

            else
                addToken(IDENT, word);//for space 

            continue;
        }

        // Operators
        if (source[pos] == '+')
        {
            addToken(PLUS, "+");
            pos++;
            continue;
        }

        else if (source[pos] == '-')
        {
            addToken(MINUS, "-");
            pos++;
            continue;
        }

        else if (source[pos] == '*')
        {
            addToken(STAR, "*");
            pos++;
            continue;
        }

        else if (source[pos] == '/')
        {
            addToken(SLASH, "/");
            pos++;
            continue;
        }

        else if (source[pos] == '=')
        {
            addToken(ASIGN, "=");
            pos++;
            continue;
        }

        else if (source[pos] == '>')
        {
            addToken(GT, ">");
            pos++;
            continue;
        }

        else if (source[pos] == '<')
        {
            addToken(LT, "<");
            pos++;
            continue;
        }

        else if (source[pos] == '{')
        {
            addToken(LBRACE, "{");
            pos++;
            continue;
        }

        else if (source[pos] == '}')
        {
            addToken(RBRACE, "}");
            pos++;
            continue;
        }

        // UNKNOWN SYMBOL HANDLING (FIXED)
else
{
    
    
        char msg[100];
        strcpy(msg, "Symbol not included in our language '");

        char sym[2];
        sym[0] = source[pos];
        sym[1] = '\0';

        strcat(msg, sym);
        strcat(msg, "'");

        throw LangError(msg);
    }

    // pos++;
    
    }
    addToken(END, "END");

}

    int getTokenCount(){
    
        return tokenCount;
    }
};

#endif