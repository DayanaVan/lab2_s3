#pragma once

#include <string>
#include <iostream>
#include <algorithm>

struct ForwardList;

struct ForwardListNode
{
    ForwardListNode *next;
    std::string key;

    ForwardListNode(std::string key);
};

struct ForwardList
{
    ForwardListNode *head;

    ForwardList();

    void insert(std::string key, int index);

    void remove(int index);

    void addHead(std::string key);

    void addTail(std::string key);

    void removeHead();

    void removeTail();

    std::string printFromHead();

    void printFromTailRec(std::string &s, ForwardListNode *node);

    std::string printFromTail();

    void removeKey(std::string key, int num);

    ForwardListNode *find(std::string key, int num);
};