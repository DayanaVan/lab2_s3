#include "hashtablecuckoo.h"

// Конструктор: создаём две пустые таблицы
HashTableCuckoo::HashTableCuckoo(int capacity)
{
    this->capacity = capacity;
    this->table1 = new Entry*[this->capacity];
    this->table2 = new Entry*[this->capacity];
    initialiseTables(); // Заполняем nullptr
}

// Деструктор
HashTableCuckoo::~HashTableCuckoo()
{
    deleteTables(this->table1, this->table2, this->capacity);
}

// Инициализация таблицы
void HashTableCuckoo::initialiseTables()
{
    for(int i = 0; i < this->capacity; i++)
    {
        this->table1[i] = nullptr;
        this->table2[i] = nullptr;
    }
}

// Вспомогательная функция для удаления таблиц
void HashTableCuckoo::deleteTables(Entry **table1, Entry **table2, int capacity)
{
    if(table1 != nullptr)
    {
        for(int i = 0; i < capacity; i++)
        {
            delete table1[i]; // Удаляем записи
        }
        delete[] table1; // Удаляем массив
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

// Рехеш: увеличиваем таблицы вдвое и переставляем все элементы
void HashTableCuckoo::rehash()
{
    Entry **oldTable1 = this->table1;
    Entry **oldTable2 = this->table2;
    int oldCapacity = this->capacity;

    this->capacity = this->capacity * 2; // Удваиваем ёмкость
    this->table1 = new Entry*[this->capacity];
    this->table2 = new Entry*[this->capacity];
    initialiseTables(); // Очищаем новые таблицы

    // Переносим все элементы из старых таблиц в новые
    for(int i = 0; i < oldCapacity; i++)
    {
        if(oldTable1[i] != nullptr && !oldTable1[i]->deleted)
        {
            insert(oldTable1[i]->key, oldTable1[i]->value);
        }
    }
    for(int i = 0; i < oldCapacity; i++)
    {
        if(oldTable2[i] != nullptr && !oldTable2[i]->deleted)
        {
            insert(oldTable2[i]->key, oldTable2[i]->value);
        }
    }

    deleteTables(oldTable1, oldTable2, oldCapacity); // Удаляем старые
}

// Первая хеш-функция (метод умножения)
int HashTableCuckoo::hash1(int key)
{
    double x = key * 0.6180339887;
    double xx = x - int(x);
    return int(xx * capacity);
}

// Вторая хеш-функция (метод деления)
int HashTableCuckoo::hash2(int key)
{
    return key % this->capacity;
}

// Вставка элемента 
void HashTableCuckoo::insert(int key, int value)
{
    // 1. Проверяем, нет ли уже такого ключа
    if(contains(key))
    {
        // Обновляем значение в той таблице, где найден ключ
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

    // 2. Пробуем вставить, вытесняя элементы 
    for(int i = 0; i < RECURSION_LIMIT; i++)
    {
        int h1 = hash1(key);
        // Пробуем вставить в первую таблицу
        if(this->table1[h1] == nullptr) // Свободное место
        {
            this->table1[h1] = new Entry{key, value, false};
            return;
        }
        else if(this->table1[h1]->deleted) // Ячейка с удалённым элементом
        {
            this->table1[h1]->key = key;
            this->table1[h1]->value = value;
            this->table1[h1]->deleted = false;
            return;
        }

        // Место занято - вытесняем элемент
        std::swap(this->table1[h1]->value, value);
        std::swap(this->table1[h1]->key, key);

        // Пробуем вставить во вторую таблицу
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

        // Вторая таблица тоже занята - вытесняем из неё
        std::swap(this->table2[h2]->value, value);
        std::swap(this->table2[h2]->key, key);
        // Цикл повторяется с новым вытесненным элементом
    }

    // Если за RECURSION_LIMIT попыток не получилось - делаем рехеш
    rehash();
    insert(key, value); // Пробуем снова
}

// Проверка наличия ключа
bool HashTableCuckoo::contains(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);
    // Проверяем в обеих таблицах
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

// Удаление элемента 
void HashTableCuckoo::remove(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);
    if(this->table1[h1] != nullptr && this->table1[h1]->key == key && !this->table1[h1]->deleted)
    {
        this->table1[h1]->deleted = true; // Просто помечаем флагом
        return;
    }
    else if(this->table2[h2] != nullptr && this->table2[h2]->key == key && !this->table2[h2]->deleted)
    {
        this->table2[h2]->deleted = true;
        return;
    }
}

// Получение значения по ключу
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
    return 0; // Не найдено
}

// Строковое представление таблиц
std::string HashTableCuckoo::toString()
{
    std::string result = "";
    // Выводим элементы из первой таблицы
    for(int i = 0; i < this->capacity; i++)
    {
        if(this->table1[i] != nullptr && !this->table1[i]->deleted)
        {
            result += std::to_string(this->table1[i]->key) + " : "
            + std::to_string(this->table1[i]->value) + " table1\n";
        }
    }
    // Выводим элементы из второй таблицы
    for(int i = 0; i < this->capacity; i++)
    {
        if(this->table2[i] != nullptr && !this->table2[i]->deleted)
        {
            result += std::to_string(this->table2[i]->key) + " : "
            + std::to_string(this->table2[i]->value) + " table2\n";
        }
    }
    return result;
}
