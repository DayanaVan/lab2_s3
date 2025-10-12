#pragma once

#include <string>
#include <vector>

struct Set
{
    struct Node
    {
        int key;
        Node *next;
    };

    int capacity;
    int size;
    Node **table;

    Set(int size);
    ~Set();

    int hash(int key);

    void add(int key);

    void remove(int key);

    bool contains(int key);

    std::string toString();

    std::vector<int> toVector();
};