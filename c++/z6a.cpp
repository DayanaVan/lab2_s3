#include <iostream>
#include "hashtablecuckoo.h"
#include "hashtabledouble.h"
#include <chrono>

using namespace std;

int main()
{
    const int ITERATIONS = 3;
    double doubleAdd = 0, doubleSearch = 0, cuckooAdd = 0, cuckooSearch = 0;
    for(int i = 0; i < ITERATIONS; i++)
    {
        cout << "Опыт " << i+1 << "\n";
        
        cout << "Кукушка:\n";
        cout << "Вставка 100 элементов = ";
        HashTableCuckoo *htc = new HashTableCuckoo(16);
        auto start_time = std::chrono::steady_clock::now();
        for(int i = 0; i < 100; i++)
        {
            htc->insert(i,i);
        }
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        cout << elapsed_ns.count() << " ns\n";
        doubleAdd += elapsed_ns.count();

        cout << "Поиск 200 элементов = ";
        start_time = std::chrono::steady_clock::now();
        for(int i = 0; i < 200; i++)
        {
            htc->contains(i);
        }
        end_time = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        cout << elapsed_ns.count() << " ns\n";
        doubleSearch += elapsed_ns.count();

        cout << "Двойное хэширование:\n";
        cout << "Вставка 100 элементов = ";
        HashTableDouble *htd = new HashTableDouble(7);
        start_time = std::chrono::steady_clock::now();
        for(int i = 0; i < 100; i++)
        {
            htd->insert(i,i);
        }
        end_time = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        cout << elapsed_ns.count() << " ns\n";
        cuckooAdd += elapsed_ns.count();

        cout << "Поиск 200 элементов = ";
        start_time = std::chrono::steady_clock::now();
        for(int i = 0; i < 200; i++)
        {
            htd->contains(i);
        }
        end_time = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        cout << elapsed_ns.count() << " ns\n\n";
        cuckooSearch += elapsed_ns.count();

        delete htd;
        delete htc;
    }
    cout << "Среднее время\n";
    cout << "Кукушка:\n";
    cout << "Вставка 100 элементов = " << cuckooAdd / (double)ITERATIONS << " ns\n";
    cout << "Поиск 200 элементов = " << cuckooSearch / (double)ITERATIONS << " ns\n";
    cout << "Двойное хэширование:\n";
    cout << "Вставка 100 элементов = " << doubleAdd / (double)ITERATIONS << " ns\n";
    cout << "Поиск 200 элементов = " << doubleSearch / (double)ITERATIONS << " ns\n";
    return 0;
}
