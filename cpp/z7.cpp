//var 2 LFU

#include "lfu.h"
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    cout << "Введите размер кэша\n";
    int cap;
    cin >> cap;
    LFU *l = new LFU(cap); 
    string command;
    while(1)
    {
        cout << "Введите команду\n";
        cin >> command;
        if(command == "exit")
        {
            break;
        }
        else if(command == "set")
        {
            int key;
            int value;
            cin >> key >> value;
            l->set(key,value);
        }
        else if(command == "get")
        {
            int key;
            cin >> key;
            printf("%d\n", l->get(key));
        }
        else
        {
            printf("Неизвестная команда\n");
        }
    }
}