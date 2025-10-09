#pragma once

#include <stdlib.h>
#include <string>

struct Array
{
    int size;
    int memorySize;
    std::string *memory;

    Array();

    void add(std::string key);

    void add(std::string key, int index);

    std::string get(int index);

    void remove(int index);

    void change(int index, std::string key);

    std::string print();
};