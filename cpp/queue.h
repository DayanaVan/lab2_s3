#pragma once

#include <string>

struct QueueNode
{
    QueueNode *next;
    std::string key;

    QueueNode(std::string key);
};

struct Queue
{
    Queue();

    QueueNode *bot;
    QueueNode *top;

    void push(std::string key);
    std::string pop();
    std::string print();
};