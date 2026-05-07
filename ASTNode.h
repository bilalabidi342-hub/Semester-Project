#ifndef ASTNode_H
#define ASTNode_H
#include<iostream>
#include<cctype>
class ASTnode{//parent class 
        public:
    virtual ~ASTnode(){};
};
class NumberNode:public ASTnode{//the main class that assingns value of number in expression
    public:
    float value;
    NumberNode(){
        value = 0;
    }
};
class IdentifyingNode : public ASTnode{
public://the class that identifies the number(mainly known as variable in easy language)
    char name[50];

    IdentifyingNode()
    {
        name[0] = '\0';
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
        varName[0] = '\0';
        expr = nullptr;
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
    ASTnode* statements[100];//since our code will have multiple parts or simply lines
    int count;

    BlockNode()
    {
        count = 0;

        for(int i = 0; i < 100; i++)
        {
            statements[i] = nullptr;
        }
    }

    void addStatement(ASTnode* node)
    {
        statements[count] = node;
        count++;
    }
};
class CompareNode : public ASTnode {
public:
    ASTnode* left;
    ASTnode* right;
    char op[3];//stores the operator as text

    CompareNode() {
        left  = nullptr;
        right = nullptr;
        op[0] = '\0';
    }
};
class IfNode : public ASTnode {
public:
    ASTnode* condition;//the comparison e.g x > 5
    ASTnode* thenBlock;//statements to run if true
    ASTnode* elseBlock;//statements to run if false

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