#include "array.h"

Array::Array()
{
    this->memorySize = 0;
    this->size = 0;
    this->memory = (block*)malloc(0 * sizeof(block));
}

void Array::add(block key)
{
    if(memorySize < size + 1)
    {
        block *oldMemory = this->memory;
        this->memorySize = size * 2 + (size == 0);
        this->memory = (block*)malloc(sizeof(block) * memorySize);
        for(int i = 0; i < size; i++)
        {
            this->memory[i] = oldMemory[i];
        }
        free(oldMemory);
    }
    this->memory[size] = key;
    this->size++;
}

void Array::add(block key, int index)
{
    if(index > size || index < 0)
        return;

    if(memorySize < size + 1)
    {
        block *oldMemory = this->memory;
        this->memorySize = size * 2 + (size == 0);
        this->memory = (block*)malloc(memorySize * sizeof(block));
        for(int i = 0; i < index; i++)
        {
            this->memory[i] = oldMemory[i];
        }
        this->memory[index] = key;
        for(int i = index + 1; i < size + 1; i++)
        {
            this->memory[i] = oldMemory[i-1];
        }
        free(oldMemory);
    }
    else
    {
        for(int i = size; i > index; i--)
        {
            this->memory[i] = this->memory[i-1];
        }
        this->memory[index] = key;
    }
    this->size++;
}

block Array::get(int index)
{
    if(index >= size || index < 0)
        return {0,0};
    return memory[index];
}

void Array::remove(int index)
{
    if(index >= size || index < 0)
        return;
    
    for(int i = index; i < size-1; i++)
    {
        this->memory[i] = this->memory[i+1];
    }
    this->size--;
}