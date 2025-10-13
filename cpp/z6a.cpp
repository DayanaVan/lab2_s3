#include <iostream>
#include "hashtablecuckoo.h"
#include "hashtabledouble.h"

using namespace std;

int main()
{
    HashTableCuckoo *htc = new HashTableCuckoo(16);
    for(int i = 0; i < 100; i++)
    {
        htc->insert(i,i);
    }
    cout << "fsdfsdfsdfsdfsdf\n";
    for(int i = 0; i < htc->capacity; i++)
    {
        /*if(htc->table1[i] != nullptr && !htc->table1[i]->deleted)
        {
            cout << htc->table1[i]->key << "\n";
        }
        if(htc->table2[i] != nullptr && !htc->table2[i]->deleted)
        {
            cout << htc->table2[i]->key << "\n";
        }*/
    }
    HashTableDouble *htd = new HashTableDouble(7);
    for(int i = 0; i < 100; i++)
    {
        htd->insert(i,i);
    }
    cout << "fsdfsdfsdfsdfsdf\n";
    for(int i = 0; i < htd->capacity; i++)
    {
        if(htd->table[i] != nullptr && !htd->table[i]->deleted)
        {
            cout << htd->table[i]->key << "\n";
        }
    }
    return 0;
}