//var 7
#include <iostream>
#include "hashtabledouble.h"

using namespace std;

int main()
{
    HashTableDouble *b_to_a = new HashTableDouble(257);
    HashTableDouble *a_to_b = new HashTableDouble(257);
    string a, b;
    getline(cin, a);
    getline(cin, b);
    if(a.size() != b.size())
    {
        cout << "Не изоморфны\n";
        return 0;
    }

    for(size_t i = 0; i < b.size(); i++)
    {
        if(b_to_a->contains(b[i]))
        {
            if(a[i] != b_to_a->get(b[i]))
            {
                cout << "Не изоморфны\n";
                return 0;
            }
        }
        else
        {
            if(a_to_b->contains(a[i]))
            {
                cout << "Не изоморфны\n";
                return 0;
            }
            b_to_a->insert(b[i], a[i]);
            a_to_b->insert(a[i], b[i]);
        }
    }
    cout << "Изоморфны\n";
}