// ASTNode.h
// Defines all AST node classes
// Each node represents one piece of the program structure
// Example: AssignNode stores a variable name and its expression
#ifndef ASTNode_H//abstract syntax tree
#define ASTNode_H
#include<iostream>
#include<cctype>
class ASTnode{//parent class 
        public:
    virtual ~ASTnode(){};//prevents memory leaks when a child node is deleted
};
class NumberNode:public ASTnode{//the main class that assingns value of number in expression
    public:
    float value;//converts all numbers we provided to a float
    NumberNode(){
        value = 0;
    }
};
class IdentifyingNode : public ASTnode{
public://the class that identifies the number(mainly known as variable in easy language)
    char name[50];//variable like x or anything

    IdentifyingNode()
    {
        name[0] = '\0';//empty string as a default
    }
};
class BinOpNode : public ASTnode{
//to identify the operator used we use this class
public:
    ASTnode* left;  //for expression on left side of op
   ASTnode* right;  //for expression on right side of op
       char op;
//ptr is used because there may be some expression on left or roght side
    BinOpNode()
    {
        left = nullptr;
        right = nullptr;
        op = '+';
    }
};
class AssignNode : public ASTnode{
//controlling function of assgnment operator
public:
    char varName[50];
    ASTnode* expr;

    AssignNode()
    {
        varName[0] = '\0';//for var on left side
        expr = nullptr;//for expression on the right side
    }
};
class PrintNode : public ASTnode{
public://it decides what to print
    ASTnode* expr;

    PrintNode()
    {
        expr = nullptr;
    }
};
class BlockNode : public ASTnode{
//this class holds the whole program
public:
//each statement value is a pointer that points to some node
    ASTnode* statements[100];//since our code will have multiple parts or simply lines
    int count;

    BlockNode()
    {
        count = 0;

        for(int i = 0; i < 100; i++)
        {
            statements[i] = nullptr;//as a default value so no garbage value is stored
        }
    }

    void addStatement(ASTnode* node)
    {
        statements[count] = node;//like mentioned before
        count++;
    }
};
class CompareNode : public ASTnode {
public:
    ASTnode* left;
    ASTnode* right;
    char op[3];//stores the operator as text(eg == texts)

    CompareNode() {
        left  = nullptr;
        right = nullptr;
        op[0] = '\0';
    }
};
class IfNode : public ASTnode {
public:
    ASTnode* condition;//the comparison eg x > 5
    ASTnode* thenBlock;//statements to run if true
    ASTnode* elseBlock;//statements to run if false or the else statemnets

    IfNode() {
        condition = nullptr;
        thenBlock = nullptr;
        elseBlock = nullptr;
    }
};
class WhileNode : public ASTnode {
public:
    ASTnode* condition;//the comparison e.g x > 7
    ASTnode* body;//statements to repeat

    WhileNode() {
        condition = nullptr;
        body      = nullptr;
    }
};
#endif