#include <algorithm>

struct HashTableCuckoo
{
    const int RECURSION_LIMIT = 10;

    struct Entry
    {
        int key;
        int value;
        bool deleted;
    };

    HashTableCuckoo(int capacity);
    ~HashTableCuckoo();

    void rehash();
    void initialiseTables();
    void deleteTables(Entry **table1, Entry **table2, int capacity);

    Entry **table1;
    Entry **table2;

    int capacity;

    int hash1(int key);
    int hash2(int key);

    void insert(int key, int value);
    bool contains(int key);
    void remove(int key);
    int get(int key);

};