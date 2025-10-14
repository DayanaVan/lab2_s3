#include "hashtabledouble.h"

HashTableDouble::HashTableDouble(int capacity)
{
    this->size = 0;
    this->capacity = capacity;
    this->table = new Entry*[this->capacity];
    for(int i = 0; i < capacity; i++)
    {
        this->table[i] = nullptr;
    }
}

HashTableDouble::~HashTableDouble()
{
    if(this->table != nullptr)
    {
        for(int i = 0; i < capacity; i++)
        {
            delete this->table[i];
        }
        delete[] this->table;
    }
}

void HashTableDouble::initialiseTable()
{
    for(int i = 0; i < this->capacity; i++)
    {
        this->table[i] = nullptr;
    }
}

void HashTableDouble::deleteTable(Entry **table, int capacity)
{
    if(table != nullptr)
    {
        for(int i = 0; i < capacity; i++)
        {
            delete table[i];
        }
        delete[] table;
    }
}

void HashTableDouble::rehash()
{
    Entry **oldTable = this->table;
    int oldCapacity = this->capacity;
    this->size = 0;

    //find new prime capacity
    this->capacity = this->capacity * 2;
    if(this->capacity % 2 == 0)
        this->capacity++;
    while (true)
    {
        bool isPrime = true;
        for (int i = 3; i * i <= this->capacity; i += 2) {
            if (this->capacity % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        
        if(isPrime)
            break;
        this->capacity += 2;
    }

    this->table = new Entry*[this->capacity];
    initialiseTable();
    for(int i = 0; i < oldCapacity; i++)
    {
        if(oldTable[i] != nullptr && !oldTable[i]->deleted)
        {
            insert(oldTable[i]->key, oldTable[i]->value);
        }
    }

    deleteTable(oldTable, oldCapacity);
}

int HashTableDouble::hash1(int key)
{
    double x = key * 0.6180339887;
    double xx = x - int(x);
    return int(xx * capacity);
}

int HashTableDouble::hash2(int key)
{
    return (key % (this->capacity - 1)) + 1;
}

bool HashTableDouble::contains(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);

    for(int i = 0; i < this->capacity; i++)
    {
        int h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr)
        {
            return false;
        }
        if(this->table[h]->key == key)
        {
            return !this->table[h]->deleted;
        }
    }
    return false;
}

void HashTableDouble::insert(int key, int value)
{
    if((double) this->size / this->capacity > MAX_LOAD)
    {
        rehash();
    }
    int h1 = hash1(key);
    int h2 = hash2(key);

    for(int i = 0; i < this->capacity; i++)
    {
        int h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr)
        {
            this->table[h] = new Entry{key, value, false};
            this->size++;
            return;
        }
        else if(this->table[h]->key == key)
        {
            this->table[h]->deleted = false;
            this->table[h]->value = value;
            return;
        }
    }
    rehash();
    insert(key, value);
}

void HashTableDouble::remove(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);

    for(int i = 0; i < this->capacity; i++)
    {
        int h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr)
        {
            return;
        }
        if(this->table[h]->key == key)
        {
            this->table[h]->deleted = true;
            return;
        }
    }
}

int HashTableDouble::get(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);

    for(int i = 0; i < this->capacity; i++)
    {
        int h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr)
        {
            return 0;
        }
        if(this->table[h]->key == key)
        {
            if(this->table[h]->deleted)
                return 0;
            else
                return this->table[h]->value;
        }
    }
    return 0;
}

std::string HashTableDouble::toString()
{
    std::string result = "";
    for(int i = 0; i < this->capacity; i++)
    {
        if(this->table[i] != nullptr && !this->table[i]->deleted)
        {
            result += std::to_string(this->table[i]->key) + " : "
            + std::to_string(this->table[i]->value) + "\n";
        }
    }
    return result;
}