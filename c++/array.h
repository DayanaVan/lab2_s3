#pragma once

#include <stdlib.h>
#include <string>

struct block
{
    int width;
    int height;
};

struct Array
{
    int size;
    int memorySize;
    block *memory;

    Array();

    void add(block key);

    void add(block key, int index);

    block get(int index);

    void remove(int index);
};