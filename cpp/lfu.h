#include <vector>

struct LFUNode
{
    int key;
    int value;
    int count;

    LFUNode(int key, int value);
};

struct LFU
{
    int cap;
    int size;

    LFUNode **items;

    LFU(int cap);

    void set(int key, int value);

    int get(int key);

    void rebalance(int key);

    void rebalance();
};