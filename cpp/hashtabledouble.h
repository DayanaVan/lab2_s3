struct HashTableDouble
{
    HashTableDouble(int size);
    ~HashTableDouble();

    struct Entry
    {
        int key;
        int value;
        bool used;
    };

};