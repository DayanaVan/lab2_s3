#include "array.h"

Array::Array()
{
    this->memorySize = 0;
    this->size = 0;
    this->memory = (std::string*)malloc(0 * sizeof(std::string));
}

void Array::add(std::string key)
{
    if(memorySize < size + 1)
    {
        std::string *oldMemory = this->memory;
        this->memorySize = size * 2 + (size == 0);
        this->memory = (std::string*)malloc(sizeof(std::string) * memorySize);
        for(int i = 0; i < size; i++)
        {
            this->memory[i] = oldMemory[i];
        }
        free(oldMemory);
    }
    this->memory[size] = key;
    this->size++;
}

void Array::add(std::string key, int index)
{
    if(index > size || index < 0)
        return;

    if(memorySize < size + 1)
    {
        std::string *oldMemory = this->memory;
        this->memorySize = size * 2 + (size == 0);
        this->memory = (std::string*)malloc(memorySize * sizeof(std::string));
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

std::string Array::get(int index)
{
    if(index >= size || index < 0)
        return "";
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

void Array::change(int index, std::string key)
{
    if(index >= size || index < 0)
        return;
    memory[index] = key;
}

std::string Array::print()
{
    std::string a = "";
    if(size == 0)
        return a;

    for(int i = 0; i < size-1; i++)
    {
        a += this->memory[i] + ' ';
    }
    a += this->memory[size-1];
    return a;
}