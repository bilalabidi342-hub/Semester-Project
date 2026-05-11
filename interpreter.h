// Interpreter.h
// Walks the AST tree and executes each node
// evaluate() returns a value from an expression
// execute() runs a statement
#ifndef INTERPRETER_H//the file that stores things in the environment
#define INTERPRETER_H
#include "ASTNode.h"//to access the nodes
#include "Environment.h"
#include <iostream>
#include <cstring>
#include "LangError.h"
using namespace std;

class Interpreter
{
    Environment env;

public:

float evaluate(ASTnode* node)
{
    if (node == nullptr)//provided node is empty
    throw LangError("ERROR: empty expression");
    //for the NumberNode case
    NumberNode* num = dynamic_cast<NumberNode*>(node);
    if (num != nullptr)
    {
        return num->value;
    }

    // for the IdentifierNode
    IdentifyingNode* id = dynamic_cast<IdentifyingNode*>(node);
    if (id != nullptr)
    {
        return env.get(id->name);
    }

    // for the operator node
    BinOpNode* bin = dynamic_cast<BinOpNode*>(node);
     if (bin != nullptr)
    {
        float left  = evaluate(bin->left);   // call is recursive and left right is to solve the right part 
        float right = evaluate(bin->right);  // and than perform op on left

        if (bin->op == '+') return left + right;
        if (bin->op == '-') return left - right;
        if (bin->op == '*') return left * right;
        if (bin->op == '/'){//error handling

    if (right == 0)
        throw LangError("ERROR: cannot divide by zero");

    return left / right;
}
    }

// CompareNode case
CompareNode* cmp = dynamic_cast<CompareNode*>(node);
if (cmp != nullptr)//new logic
{
    float left  = evaluate(cmp->left);
    float right = evaluate(cmp->right);

    if (strcmp(cmp->op, ">")  == 0) return left > right ? 1.0f : 0.0f;
    if (strcmp(cmp->op, "<")  == 0) return left < right ? 1.0f : 0.0f;
    if (strcmp(cmp->op, "==") == 0) return left == right ? 1.0f : 0.0f;
}

    //Default case
    throw LangError("ERRRO: issue in the expression");
    return 0;
}


// execute to execute the code
void execute(ASTnode* node)
{
    // AssignNode case
    AssignNode* assign = dynamic_cast<AssignNode*>(node);
    if (assign != nullptr)
    {
        float result = evaluate(assign->expr);//variable and its value(RESULT)
        env.set(assign->varName, result);
        return;
    }

    // PrintNode case
    PrintNode* print = dynamic_cast<PrintNode*>(node);
    if (print != nullptr)
    {
        float result = evaluate(print->expr);
        cout << result << endl;//to mainly print the result
        return;
    }

    // BlockNode case
    BlockNode* block = dynamic_cast<BlockNode*>(node);
    if (block != nullptr)
    {
        for (int i = 0; i < block->count; i++)
        {
            execute(block->statements[i]);//to run all statments by once
        }
        return;
    }

    // IfNode case
    IfNode* ifNode = dynamic_cast<IfNode*>(node);
    if (ifNode != nullptr)
    {
        float result = evaluate(ifNode->condition);
        if (result != 0)
            execute(ifNode->thenBlock);
        else if (ifNode->elseBlock != nullptr)
            execute(ifNode->elseBlock);
        return;
    }

    // WhileNode case
    WhileNode* whileNode = dynamic_cast<WhileNode*>(node);
    if (whileNode != nullptr)//new logics
    {
        while (true)
        {
            float result = evaluate(whileNode->condition);
            if (result == 0) break;
            execute(whileNode->body);
        }
        return;
    }

    throw LangError("ERROR: unknown statement");//stops execution of program
}


// boss run function
void run(ASTnode* tree)
{
    execute(tree);
}

};

#endif