#include "lfu.h"


LFUNode::LFUNode(int key, int value)
{
    this->key = key;
    this->value = value;
    this->count = 0;
}

LFU::LFU(int cap)
{
    this->cap = cap;
    this->items = new LFUNode*[cap];
    this->size = 0;
}

void LFU::set(int key, int value)
{
    for(int i = 0; i < this->size; i++)//changing
    {
        if(this->items[i]->key == key)
        {
            this->items[i]->value = value;
            rebalance(key);
            return;
        }
    }
    if(this->size < this->cap) //adding
    {
        this->items[size] = new LFUNode(key, value);
        this->size++;
    }
    else
    {
        delete this->items[0];
        for(int i = 1; i < cap; i++)
        {
            this->items[i-1] = this->items[i];
        }
        this->items[this->cap - 1] = new LFUNode(key, value);
    }
}

int LFU::get(int key)
{
    for(int i = 0; i < this->size; i++)
    {
        if(this->items[i]->key == key)
        {
            int toReturn = this->items[i]->value;
            rebalance(key);
            return toReturn;
        }
    }
    return -1;
}

void LFU::rebalance(int key)
{
    for(int i = 0; i < this->size; i++)
    {
        if(this->items[i]->key == key)
        {
            this->items[i]->count++;
            for(int g = i+1; g < this->size; g++)
            {
                if(this->items[g-1]->count >= this->items[g]->count)
                    std::swap(this->items[g-1], this->items[g]);
            }
            break;
        }
    }
}