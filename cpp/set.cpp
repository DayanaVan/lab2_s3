#include "set.h"

Set::Set(int capacity)
{
    this->capacity = capacity;
    this->size = 0;
    this->table = new Node*[capacity];
    for (int i = 0; i < capacity; i++)
    {
        this->table[i] = nullptr;
    }
}

Set::~Set()
{
    if(this->table == nullptr)
        return;
    for(int i = 0; i < capacity; i++)
    {
        Node *n = this->table[i];
        while(n != nullptr)
        {
            Node* toDelete = n;
            n = n->next;
            delete toDelete;
        }
    }
    delete[] this->table;
}

int Set::hash(int key)
{
    double x = key * 0.6180339887;
    double xx = x - int(x);
    return int(xx * capacity);
}

void Set::add(int key)
{
    if(contains(key))
        return;

    this->size++;
    int h = this->hash(key);
    Node *n = this->table[h];
    if(n == nullptr)
    {
        this->table[h] = new Node{key, nullptr};
        return;
    }
    while(n->next != nullptr)
    {
        n = n->next;
    }
    n->next = new Node{key, nullptr};
}

void Set::remove(int key)
{
    int h = hash(key);
    Node *n = this->table[h];
    if(n == nullptr)
        return;
    if(n->key == key)
    {
        this->table[h] = n->next;
        delete n;
        this->size--;
        return;
    }
    while(n->next != nullptr)
    {
        if(n->next->key == key)
        {
            Node *toDelete = n->next;
            n->next = toDelete->next;
            delete n;
            this->size--;
            return;
        }
        n = n->next;
    }
}

bool Set::contains(int key)
{
    int h = hash(key);
    Node *n = this->table[h];
    while(n != nullptr)
    {
        if(n->key == key)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

std::string Set::toString()
{
    std::string a = "";
    for(int i = 0; i < capacity; i++)
    {
        Node *n = this->table[i];
        while(n != nullptr)
        {
            a += std::to_string(n->key) + " ";
            n = n->next;
        }
    }
    return a;
}

std::vector<int> Set::toVector()
{
    std::vector<int> a;
    for(int i = 0; i < capacity; i++)
    {
        Node *n = this->table[i];
        while(n != nullptr)
        {
            a.push_back(n->key);
            n = n->next;
        }
    }
    return a;
}