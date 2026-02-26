#include <vector>

struct LFUNode
{
    int key, value, count;
    LFUNode(int key, int value);
};

struct LFU
{
    int cap, size;
    LFUNode **items; // Упорядоченный по частоте массив указателей

    LFU(int cap);
    void set(int key, int value);
    int get(int key);
    void rebalance(int key);      // Увеличение счётчика конкретного элемента
    void rebalance();             // Полная сортировка массива
};
