#include "hashtablecuckoo.h"

HashTableCuckoo::HashTableCuckoo(int capacity)
{
    this->capacity = capacity;
    this->table1 = new Entry*[this->capacity];
    this->table2 = new Entry*[this->capacity];
    initialiseTables();
}

HashTableCuckoo::~HashTableCuckoo()
{
    deleteTables(this->table1, this->table2, this->capacity);
}

void HashTableCuckoo::initialiseTables()
{
    for(int i = 0; i < this->capacity; i++)
    {
        this->table1[i] = nullptr;
        this->table2[i] = nullptr;
    }
}

void HashTableCuckoo::deleteTables(Entry **table1, Entry **table2, int capacity)
{
    if(table1 != nullptr)
    {
        for(int i = 0; i < capacity; i++)
        {
            delete table1[i];
        }
        delete[] table1;
    }
    if(table2 != nullptr)
    {
        for(int i = 0; i < capacity; i++)
        {
            delete table2[i];
        }
        delete[] table2;
    }
}

void HashTableCuckoo::rehash()
{
    Entry **oldTable1 = this->table1;
    Entry **oldTable2 = this->table2;
    int oldCapacity = this->capacity;

    this->capacity = this->capacity * 2;
    this->table1 = new Entry*[this->capacity];
    this->table2 = new Entry*[this->capacity];
    initialiseTables();
    for(int i = 0; i < oldCapacity; i++)
    {
        if(oldTable1[i] != nullptr && !oldTable1[i]->deleted)
        {
            insert(oldTable1[i]->key, oldTable1[i]->value);
        }
        if(oldTable2[i] != nullptr && !oldTable2[i]->deleted)
        {
            insert(oldTable2[i]->key, oldTable2[i]->value);
        }
    }

    deleteTables(oldTable1, oldTable2, oldCapacity);
}

int HashTableCuckoo::hash1(int key)
{
    double x = key * 0.6180339887;
    double xx = x - int(x);
    return int(xx * capacity);
}

int HashTableCuckoo::hash2(int key)
{
    return key % this->capacity;
}

void HashTableCuckoo::insert(int key, int value)
{
    if(contains(key))
    {
        int h1 = hash1(key);
        int h2 = hash2(key);
        if(this->table1[h1] != nullptr && this->table1[h1]->key == key && !this->table1[h1]->deleted)
        {
            this->table1[h1]->value = value;
            return;
        }
        else if(this->table2[h2] != nullptr && this->table2[h2]->key == key && !this->table2[h2]->deleted)
        {
            this->table2[h2]->value = value;
            return;
        }
    }
    for(int i = 0; i < RECURSION_LIMIT; i++)
    {
        int h1 = hash1(key);
        if(this->table1[h1] == nullptr)
        {
            this->table1[h1] = new Entry{key, value, false};
            return;
        }
        else if(this->table1[h1]->deleted)
        {
            this->table1[h1]->key = key;
            this->table1[h1]->value = value;
            this->table1[h1]->deleted = false;
            return;
        }
        std::swap(this->table1[h1]->value, value);
        std::swap(this->table1[h1]->key, key);
        int h2 = hash2(key);
        if(this->table2[h2] == nullptr)
        {
            this->table2[h2] = new Entry{key, value, false};
            return;
        }
        else if(this->table2[h2]->deleted)
        {
            this->table2[h2]->key = key;
            this->table2[h2]->value = value;
            this->table2[h2]->deleted = false;
            return;
        }
        std::swap(this->table2[h2]->value, value);
        std::swap(this->table2[h2]->key, key);
    }
    rehash();
    insert(key, value);
}

bool HashTableCuckoo::contains(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);
    if(this->table1[h1] != nullptr && this->table1[h1]->key == key && !this->table1[h1]->deleted)
    {
        return true;
    }
    else if(this->table2[h2] != nullptr && this->table2[h2]->key == key && !this->table2[h2]->deleted)
    {
        return true;
    }
    return false;
}

void HashTableCuckoo::remove(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);
    if(this->table1[h1] != nullptr && this->table1[h1]->key == key && !this->table1[h1]->deleted)
    {
        this->table1[h1]->deleted = true;
        return;
    }
    else if(this->table2[h2] != nullptr && this->table2[h2]->key == key && !this->table2[h2]->deleted)
    {
        this->table2[h2]->deleted = true;
        return;
    }
}

int HashTableCuckoo::get(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);
    if(this->table1[h1] != nullptr && this->table1[h1]->key == key && !this->table1[h1]->deleted)
    {
        return this->table1[h1]->value;
    }
    else if(this->table2[h2] != nullptr && this->table2[h2]->key == key && !this->table2[h2]->deleted)
    {
        return this->table2[h2]->value;
    }
    return 0;
}