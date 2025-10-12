//var 2 LFU

#include "lfu.h"
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int cap, n;
    cin >> cap >> n;
    LFU *l = new LFU(cap); 
    string command;
    for(int i = 0; i < n; i++)
    {
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