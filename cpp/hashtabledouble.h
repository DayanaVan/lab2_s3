#pragma once

#include <string>
#include <iostream>

struct HashTableDouble
{
    const double MAX_LOAD = 0.75;
    HashTableDouble(int capacity);
    ~HashTableDouble();

    struct Entry
    {
        int key;
        int value;
        bool deleted;
    };

    Entry **table;
    int capacity;
    int size;

    void rehash();
    void initialiseTable();
    void deleteTable(Entry **table, int capacity);

    int hash1(int key);
    int hash2(int key);

    void insert(int key, int value);
    bool contains(int key);
    void remove(int key);
    int get(int key);

    std::string toString();
};