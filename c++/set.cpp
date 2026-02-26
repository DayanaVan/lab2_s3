#include "set.h"

// Создаём хеш-таблицу заданной ёмкости
Set::Set(int capacity)
{
    this->capacity = capacity;
    this->size = 0;
    this->table = new Node*[capacity]; // Массив указателей на начала списков
    for (int i = 0; i < capacity; i++)
    {
        this->table[i] = nullptr; // Изначально все списки пусты
    }
}

// Деструктор: освобождаем всю память
Set::~Set()
{
    if(this->table == nullptr)
        return;
    for(int i = 0; i < capacity; i++)
    {
        Node *n = this->table[i];
        while(n != nullptr) // Проходим по списку и удаляем каждый узел
        {
            Node* toDelete = n;
            n = n->next;
            delete toDelete;
        }
    }
    delete[] this->table; // Удаляем массив указателей
}

// Хеш-функция методом умножения 
int Set::hash(int key)
{
    double x = key * 0.6180339887;    // Умножаем на константу
    double xx = x - int(x);            // Берём дробную часть
    return int(xx * capacity);         // Умножаем на размер таблицы
}

// Добавление элемента в множество
void Set::add(int key)
{
    if(contains(key)) // Проверяем, нет ли уже такого ключа
        return;

    this->size++;
    int h = this->hash(key);
    Node *n = this->table[h];
    if(n == nullptr) // Если список пуст, создаём первый узел
    {
        this->table[h] = new Node{key, nullptr};
        return;
    }
    // Иначе идём в конец списка и добавляем новый узел
    while(n->next != nullptr)
    {
        n = n->next;
    }
    n->next = new Node{key, nullptr};
}

// Удаление элемента из множества
void Set::remove(int key)
{
    int h = hash(key);
    Node *n = this->table[h];
    if(n == nullptr)
        return;
    
    // Удаляем первый элемент списка
    if(n->key == key)
    {
        this->table[h] = n->next;
        delete n;
        this->size--;
        return;
    }
    
    // Ищем элемент в середине или конце списка
    while(n->next != nullptr)
    {
        if(n->next->key == key)
        {
            Node *toDelete = n->next;
            n->next = toDelete->next;
            delete toDelete; // Удаляем найденный узел
            this->size--;
            return;
        }
        n = n->next;
    }
}

// Проверка наличия элемента
bool Set::contains(int key)
{
    int h = hash(key);
    Node *n = this->table[h];
    while(n != nullptr) // Проходим по всему списку
    {
        if(n->key == key)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Преобразование множества в строк
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

// Преобразование множества в вектор
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
