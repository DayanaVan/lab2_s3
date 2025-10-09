#include "stack.h"

StackNode::StackNode(std::string key)
{
    this->prev = nullptr;
    this->key = key;
}

Stack::Stack()
{
    this->top = nullptr;
}

void Stack::push(std::string key)
{
    StackNode *newNode = new StackNode(key);
    if(this->top == nullptr)
    {
        this->top = newNode;
        return;
    }

    newNode->prev = this->top;
    this->top = newNode;
}

std::string Stack::pop()
{
    if(this->top == nullptr)
        return "";
    StackNode *node = this->top;
    this->top = node->prev;
    std::string ret = node->key;
    delete node;
    return ret;
}

std::string Stack::print()
{
    StackNode *node = this->top;
    if(node == nullptr)
        return "";

    std::string a = "";
    while(node->prev != nullptr)
    {
        a += node->key + " ";
        node = node->prev;
    }
    a += node->key;
    return a;
}