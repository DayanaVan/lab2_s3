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

    int capacity;   // Размер таблицы
    int size;       // Количество элементов
    Node **table;   // Массив указателей на списки

    Set(int size);
    ~Set();

    int hash(int key);          // Хеш-функция (метод умножения)
    void add(int key);
    void remove(int key);
    bool contains(int key);
    std::string toString();
    std::vector<int> toVector();
};
