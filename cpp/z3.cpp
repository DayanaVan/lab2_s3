//var 4

#include <iostream>
#include "set.h"
#include <vector>
#include <algorithm>

using namespace std;

Set *intersection(Set* a, Set* b)
{
    Set *in = new Set(32);
    vector<int> aVector = a->toVector();
    for (size_t i = 0; i < aVector.size(); i++)
    {
        if (b->contains(aVector[i]))
        {
            in->add(aVector[i]);
        }
    }
    return in;
}

int main()
{
    cout << "Введите количество множеств\n";
    int n;
    cin >> n;
    if (n < 2)
        return 1;
    Set **sets = new Set*[n];
    for (int i = 0; i < n; i++)
    {
        sets[i] = new Set(32);
        cout << "Введите количество элементов в множестве\n";
        int nn;
        cin >> nn;
        cout << "Введите множество\n";
        for (int j = 0; j < nn; j++)
        {
            int a;
            cin >> a;
            sets[i]->add(a);
        }
    }
    int result1 = 0, result2 = 0, resultSize = 0;
    Set *result = nullptr;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (j == i)
                continue;
            Set *in = intersection(sets[i], sets[j]);
            if (in->size > resultSize)
            {
                delete result;
                resultSize = in->size;
                result1 = i;
                result2 = j;
                result = in;
            }
            else
            {
                delete in;
            }
        }
    }
    if (resultSize != 0)
    {
        cout << "Пересечение: {" << sets[result1]->toString() << "} и {" << sets[result2]->toString() << "} = {"
            << result->toString() << "}";
    }
    else
    {
        cout << "Пересечений нет";
    }
}