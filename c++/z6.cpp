#include <iostream>
#include "hashtabledouble.h"

using namespace std;

int main()
{
    cout << "Введите две строки:\n";
    HashTableDouble *b_to_a = new HashTableDouble(257); // Отображение b->a
    HashTableDouble *a_to_b = new HashTableDouble(257); // Отображение a->b
    string a, b;
    getline(cin, a);
    getline(cin, b);
    cout << "Вывод: ";
    if(a.size() != b.size())
    {
        cout << "Не изоморфны\n";
        return 0;
    }

    // Проверка взаимно-однозначного соответствия символов
    for(size_t i = 0; i < b.size(); i++)
    {
        if(b_to_a->contains(b[i]))
        {
            // Символ из b уже сопоставлен — проверяем соответствие
            if(a[i] != b_to_a->get(b[i]))
            {
                cout << "Не изоморфны\n";
                return 0;
            }
        }
        else
        {
            // Новое сопоставление: символ a не должен быть уже сопоставлен
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
