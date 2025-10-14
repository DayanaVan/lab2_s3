#include <iostream>
#include "hashtablecuckoo.h"
#include "hashtabledouble.h"
#include <chrono>

using namespace std;

int main()
{
    for(int i = 0; i < 3; i++)
    {
        cout << "Опыт " << i+1 << " --------\n";

        cout << "Кукушка:\n";
        cout << "Вставка 100 элементов - ";
        HashTableCuckoo *htc = new HashTableCuckoo(16);
        auto start_time = std::chrono::steady_clock::now();
        for(int i = 0; i < 100; i++)
        {
            htc->insert(i,i);
        }
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        cout << elapsed_ns.count() << " ns\n";

        cout << "Поиск 100 элементов = ";

        start_time = std::chrono::steady_clock::now();
        for(int i = 0; i < 100; i++)
        {
            htc->contains(i);
        }
        end_time = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        cout << elapsed_ns.count() << " ns\n";

        cout << "Двойное хэширование\n";
        cout << "Вставка 100 элементов - ";
        HashTableDouble *htd = new HashTableDouble(7);
        start_time = std::chrono::steady_clock::now();
        for(int i = 0; i < 100; i++)
        {
            htd->insert(i,i);
        }
        end_time = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        cout << elapsed_ns.count() << " ns\n";

        cout << "Поиск 100 элементов = ";

        start_time = std::chrono::steady_clock::now();
        for(int i = 0; i < 100; i++)
        {
            htd->contains(i);
        }
        end_time = std::chrono::steady_clock::now();
        elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        cout << elapsed_ns.count() << " ns\n";
        delete htd;
        delete htc;
    }
    return 0;
}