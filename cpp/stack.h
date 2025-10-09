#pragma once

#include <string>

struct StackNode
{
    StackNode *prev;
    std::string key;

    StackNode(std::string key);
};

struct Stack
{
    Stack();

    StackNode *top;

    void push(std::string key);
    std::string pop();
    std::string print();
};