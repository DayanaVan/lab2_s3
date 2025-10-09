#include "queue.h"

QueueNode::QueueNode(std::string key)
{
    this->next = nullptr;
    this->key = key;
}

Queue::Queue()
{
    this->bot = nullptr;
    this->top = nullptr;
}

void Queue::push(std::string key)
{
    QueueNode *newNode = new QueueNode(key);
    if(this->top == nullptr)
    {
        this->bot = newNode;
        this->top = newNode;
        return;
    }

    this->top->next = newNode;
    this->top = newNode;
}

std::string Queue::pop()
{
    if(this->bot == nullptr)
        return "";

    QueueNode *node = this->bot;
    this->bot = node->next;
    if(this->bot == nullptr)
        this->top = nullptr;
    std::string ret = node->key;
    delete node;
    return ret;
}

std::string Queue::print()
{
    QueueNode *node = this->bot;
    if(node == nullptr)
        return "";

    std::string a = "";
    while(node->next != nullptr)
    {
        a += node->key + " ";
        node = node->next;
    }
    a += node->key;
    return a;
}