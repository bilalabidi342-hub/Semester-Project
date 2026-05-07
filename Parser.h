#ifndef PARSER_H
#define PARSER_H
#include "Token.h"//already defined
#include "ASTNode.h"//the converter of nodes file
#include <cstring>
#include <cstdlib>//for atoi and atof funcs
#include "LangError.h"

class Parser
{
private:
Token* tokens;//poins to token array in lexer file
int pos;//to track the position of the lexer
int totalTokens;//total tokens

public:

Parser(Token* t, int count){//when called than it starts implementing logic of reading tokens

    tokens = t;
    totalTokens = count;
    pos = 0;//to start from 0th index
}

Token currentToken(){//tracks the current position but doesnt move

    if (pos >= totalTokens)
        throw LangError("ERROR: code is incomplete");

    return tokens[pos];
}

Token consume(){//tracks the current position and mives forward

   if (pos >= totalTokens)//means the tokens are finished but doesnt mean the array memory has finished
      throw LangError("ERROR: code is incomplete");//the user actually missed something

    return tokens[pos++];
}

ASTnode* parsePrimary()//for checking simple funcs
{
    Token t = currentToken();//to check the current token

    if (t.type == NUMBER)//to cehck the number
    {
        NumberNode* num = new NumberNode();

        num->value = atof(t.value);//converts text to the number

        consume();//moves to next token

        return num;
    }

    if (t.type == IDENT)//for the plus minus operator
    {
        IdentifyingNode* id = new IdentifyingNode();

        strcpy(id->name, t.value);//copying 

        consume();

        return id;
    }

    throw LangError("ERROR: expression was not understandable");
}

ASTnode* parseExpression()
{
    // First get the left side
    ASTnode* left = parsePrimary();

    // Check if next token is an operator
    if (currentToken().type == PLUS ||
        currentToken().type == MINUS ||
        currentToken().type == STAR ||
        currentToken().type == SLASH)
    {
        // Store operator token
        Token opToken = consume();

        // Create Binary Operation Node
        BinOpNode* binOp = new BinOpNode();

        // Set left side
        binOp->left = left;

        // Store actual operator symbol
        if (opToken.type == PLUS)
            binOp->op = '+';
        else if (opToken.type == MINUS)
            binOp->op = '-';
        else if (opToken.type == STAR)
            binOp->op = '*';
        else if (opToken.type == SLASH)
            binOp->op = '/';

        // Parse right side
        binOp->right = parsePrimary();

        // Return full expression node
        return binOp;
    }
    // handle comparison operators(new logic after fixation)
if (currentToken().type == GT  ||
    currentToken().type == LT  ||
    currentToken().type == EQEQ)
{
    Token opToken = consume();

    CompareNode* cmp = new CompareNode();
    cmp->left = left;

    if (opToken.type == GT)   strcpy(cmp->op, ">");
    if (opToken.type == LT)   strcpy(cmp->op, "<");
    if (opToken.type == EQEQ) strcpy(cmp->op, "==");

    cmp->right = parsePrimary();

    return cmp;
}

    // If no operator exists, just return single value
    return left;
}
ASTnode* parseBlock()//new logic
{
    if (currentToken().type != LBRACE)
        throw LangError("ERROR: { expected");

    consume(); // eat {

    BlockNode* block = new BlockNode();

    while (currentToken().type != RBRACE && 
           currentToken().type != END)
    {
        ASTnode* stmt = parseStatement();
        if (stmt != nullptr)
            block->addStatement(stmt);
        else
            consume();
    }

    if (currentToken().type != RBRACE)
        throw LangError("ERROR: } expected");

    consume(); // eat }

    return block;
}

ASTnode* parseStatement()
{
    Token t = currentToken();
    // AGAR (if statement)
if (t.type == AGAR)
{
    consume(); // eat "agar"

    IfNode* ifNode = new IfNode();

    ifNode->condition = parseExpression();
    ifNode->thenBlock = parseBlock();

    // check for warna (else)
    if (currentToken().type == WARNA)
    {
        consume(); // eat "warna"
        ifNode->elseBlock = parseBlock();
    }

    return ifNode;
}

// JABTAK (while loop)
if (t.type == JABTAK)
{
    consume(); // eat "jabtak"

    WhileNode* whileNode = new WhileNode();

    whileNode->condition = parseExpression();
    whileNode->body      = parseBlock();

    return whileNode;
}

    // PRINT STATEMENT 
    // Example: print x
    if (t.type == PRINT)
    {
        // move afetr the print 
        consume();

        if (currentToken().type == END)
            throw LangError("ERROR: Some expression is needed after the = ");

        // create PrintNode
        PrintNode* printNode = new PrintNode();

        // parse what comes after print
        printNode->expr = parseExpression();

        return printNode;
    }

    // ASSIGNMENT STATEMENT
    // Example: x = 5 + 3
    if (t.type == IDENT)
    {
        // create the assignNode
        AssignNode* assignNode = new AssignNode();

        // store(copy) variable name
        strcpy(assignNode->varName, t.value);

        // move past variable name
        consume();

        // check if next token is =
        if (currentToken().type == ASIGN)
        {
            // move past "="
            consume();

            if (currentToken().type == END)
                throw LangError("ERROR: something needed after the = expression");

            // parse right side expression
            assignNode->expr = parseExpression();

            return assignNode;
        }

        throw LangError("ERROR: expected = after identifier");
    }

    return nullptr;
}

ASTnode* parse()
{
    BlockNode* block = new BlockNode();// Creates a full program block

    // Keep parsing until END token comes
    while (currentToken().type != END)
    {
        // Parse one statement
        ASTnode* stmt = parseStatement();

        // If valid statement found, add it to block
        if (stmt != nullptr)
        {
            block->addStatement(stmt);
        }
        else
        {
            consume(); // skip unrecognized token and continue
        }
    }

    // Return complete program
    return block;
}

};

#endif