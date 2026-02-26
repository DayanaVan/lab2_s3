#include <iostream>
#include "hashtablecuckoo.h"
#include "hashtabledouble.h"

using namespace std;

int main()
{
    cout << "Выберите метод: 1 - двойное хэширование; 2 - кукушка\n";
    string hashMethod;
    cin >> hashMethod;
    if(hashMethod == "1")
    {
        HashTableDouble *htd = new HashTableDouble(7);
        while(1)
        {
            cout << "Введите команду:\n";
            string command;
            cin >> command;
            if(command == "insert")
            {
                int key, value;
                cin >> key >> value;
                htd->insert(key, value);
                cout << htd->toString();
            }
            else if(command == "remove")
            {
                int key;
                cin >> key;
                htd->remove(key);
                cout << htd->toString();
            }
            else if(command == "contains")
            {
                int key;
                cin >> key;
                if(htd->contains(key))
                {
                    cout << "Найдено\n";
                }
                else
                {
                    cout << "Не найдено\n";
                }
            }
            else if(command == "get")
            {
                int key;
                cin >> key;
                cout << htd->get(key) << "\n";
            }
            else if(command == "exit")
            {
                return 0;
            }
            else
            {
                cout << "Неизвестная команда\n";
            }
        }
    }
    else if(hashMethod == "2")
    {
        HashTableCuckoo *htc = new HashTableCuckoo(8);
        while(1)
        {
            cout << "Введите команду\n";
            string command;
            cin >> command;
            if(command == "insert")
            {
                int key, value;
                cin >> key >> value;
                htc->insert(key, value);
                cout << htc->toString();
            }
            else if(command == "remove")
            {
                int key;
                cin >> key;
                htc->remove(key);
                cout << htc->toString();
            }
            else if(command == "contains")
            {
                int key;
                cin >> key;
                if(htc->contains(key))
                {
                    cout << "Найдено\n";
                }
                else
                {
                    cout << "Не найдено\n";
                }
            }
            else if(command == "get")
            {
                int key;
                cin >> key;
                cout << htc->get(key) << "\n";
            }
            else if(command == "exit")
            {
                return 0;
            }
            else
            {
                cout << "Неизвестная команда\n";
            }
        }
    }
}
