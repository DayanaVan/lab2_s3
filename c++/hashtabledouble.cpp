#include "hashtabledouble.h"

// Конструктор: создаём пустую таблицу
HashTableDouble::HashTableDouble(int capacity)
{
    this->size = 0;
    this->capacity = capacity;
    this->table = new Entry*[this->capacity]; // Массив указателей
    initialiseTable(); // Заполняем nullptr
}

// Деструктор: освобождаем память
HashTableDouble::~HashTableDouble()
{
    if(this->table != nullptr)
    {
        for(int i = 0; i < capacity; i++)
        {
            delete this->table[i]; // Удаляем каждую запись
        }
        delete[] this->table; // Удаляем массив
    }
}

// Инициализация таблицы 
void HashTableDouble::initialiseTable()
{
    for(int i = 0; i < this->capacity; i++)
    {
        this->table[i] = nullptr;
    }
}

// Вспомогательная функция для удаления таблицы
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

// Рехеш: увеличиваем таблицу и переставляем все элементы
void HashTableDouble::rehash()
{
    Entry **oldTable = this->table;   // Сохраняем старую таблицу
    int oldCapacity = this->capacity; // Сохраняем старую ёмкость
    this->size = 0; // Сбрасываем счётчик

    // Увеличиваем ёмкость до следующего простого числа
    this->capacity = this->capacity * 2;
    if(this->capacity % 2 == 0)
        this->capacity++; // Делаем нечётным
    
    // Поиск ближайшего простого числа
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
        this->capacity += 2; // Остаёмся нечётными
    }

    // Создаём новую таблицу
    this->table = new Entry*[this->capacity];
    initialiseTable();
    
    // Перемещаем все элементы из старой таблицы в новую
    for(int i = 0; i < oldCapacity; i++)
    {
        if(oldTable[i] != nullptr && !oldTable[i]->deleted)
        {
            insert(oldTable[i]->key, oldTable[i]->value);
        }
    }

    deleteTable(oldTable, oldCapacity); // Удаляем старую таблицу
}

// Первая хеш-функция (метод умножения) - определяет начальную позицию
int HashTableDouble::hash1(int key)
{
    double x = key * 0.6180339887;
    double xx = x - int(x);
    return int(xx * capacity);
}

// Вторая хеш-функция - определяет шаг
int HashTableDouble::hash2(int key)
{
    return (key % (this->capacity - 1)) + 1;
}

// Проверка наличия ключа
bool HashTableDouble::contains(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);

    for(int i = 0; i < this->capacity; i++)
    {
        int h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr) // Встретили пустую ячейку - ключа нет
        {
            return false;
        }
        if(this->table[h]->key == key) // Нашли по ключу
        {
            return !this->table[h]->deleted; // Проверяем, не удалён ли
        }
    }
    return false;
}

// Вставка элемента
void HashTableDouble::insert(int key, int value)
{
    // Проверяем, не превышен ли коэффициент заполнения
    if((double) this->size / this->capacity > MAX_LOAD)
    {
        rehash(); // Увеличиваем таблицу
    }

    int h1 = hash1(key);
    int h2 = hash2(key);

    for(int i = 0; i < this->capacity; i++)
    {
        int h = (h1 + i * h2) % this->capacity;

        if(this->table[h] == nullptr) // Нашли пустую ячейку
        {
            this->table[h] = new Entry{key, value, false};
            this->size++;
            return;
        }
        else if(this->table[h]->key == key) // Нашли такой же ключ
        {
            // Обновляем значение и снимаем флаг удаления
            this->table[h]->deleted = false;
            this->table[h]->value = value;
            return; // Размер не увеличивается
        }
    }
    
    // Если не нашли места, делаем рехеш и пробуем снова
    rehash();
    insert(key, value);
}

// Удаление 
void HashTableDouble::remove(int key)
{
    int h1 = hash1(key);
    int h2 = hash2(key);

    for(int i = 0; i < this->capacity; i++)
    {
        int h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr) // До пустоты - ключа нет
        {
            return;
        }
        if(this->table[h]->key == key) // Нашли ключ
        {
            this->table[h]->deleted = true; // Помечаем как удалённый
            return;
        }
    }
}

// Получение значения по ключу
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
