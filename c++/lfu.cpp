#include "lfu.h"
#include <algorithm> 

// Конструктор узла 
LFUNode::LFUNode(int key, int value)
{
    this->key = key;
    this->value = value;
    this->count = 0; // Счётчик обращений изначально 0
}

// Конструктор LFU-кэша
LFU::LFU(int cap)
{
    this->cap = cap;                         // Максимальный размер кэша
    this->items = new LFUNode*[cap];         // Массив указателей на узлы
    this->size = 0;                         
}

// Установка значения (вставка или обновление)
void LFU::set(int key, int value)
{
    // 1. Пытаемся найти элемент с таким ключом 
    for(int i = 0; i < this->size; i++)
    {
        if(this->items[i]->key == key) // Нашли существующий ключ
        {
            this->items[i]->value = value;    // Обновляем значение
            rebalance(key);                    // Увеличиваем счётчик и пересортируем
            return;
        }
    }

    // 2. Если ключ не найден, добавляем новый
    if(this->size < this->cap) // Есть свободное место
    {
        this->items[size] = new LFUNode(key, value); // Добавляем в конец
        this->size++;
    }
    else // Места нет - нужно вытеснить наименее часто используемый
    {
        delete this->items[0]; // Удаляем его

        // Сдвигаем все элементы влево
        for(int i = 1; i < cap; i++)
        {
            this->items[i-1] = this->items[i];
        }
        // В конец кладём новый элемент
        this->items[this->cap - 1] = new LFUNode(key, value);
    }
    // После вставки нового элемента делаем полную перебалансировку
    rebalance();
}

// Получение значения по ключу
int LFU::get(int key)
{
    for(int i = 0; i < this->size; i++)
    {
        if(this->items[i]->key == key) // Нашли ключ
        {
            int toReturn = this->items[i]->value; // Запоминаем значение
            rebalance(key); // Увеличиваем счётчик и пересортируем
            return toReturn;
        }
    }
    return -1; // Ключ не найден
}

// Полная перебалансировка (
void LFU::rebalance()
{
    for(int i = 0; i < this->size; i++)
    {
        for(int j = 0; j < this->size-1-i; j++)
        {
            // Если текущий элемент используется чаще следующего
            if(this->items[j]->count > this->items[j+1]->count)
            {
                std::swap(this->items[j], this->items[j+1]); // Меняем местами
            }
        }
    }
}

// Перебалансировка после обращения к конкретному ключу
void LFU::rebalance(int key)
{
    for(int i = 0; i < this->size; i++)
    {
        if(this->items[i]->key == key) // Нашли нужный узел
        {
            this->items[i]->count++; // Увеличиваем счётчик обращений

            // "Всплытие" элемента вправо, пока его счётчик больше, чем у правых соседей
            for(int g = i+1; g < this->size; g++)
            {
                // При равных счётчиках порядок сохраняется
                if(this->items[g-1]->count >= this->items[g]->count)
                    std::swap(this->items[g-1], this->items[g]);
            }
            break;
        }
    }
}
