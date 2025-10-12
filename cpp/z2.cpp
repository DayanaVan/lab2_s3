#include <iostream>
#include <fstream>
#include <cstring>
#include "set.h"

using namespace std;

void printHelp()
{
    cout << "Usage: ./z2 [FILE] [COMMAND] [ARGUMENTS]\n";
}

void writeSet(ofstream &ofs, Set *set)
{
    ofs << set->toString();
}

void readSet(ifstream &ifs, Set *set)
{
    int a;
    while(ifs >> a)
    {
        set->add(a);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        printHelp();
        return 0;
    }

    string file(argv[1]);
    ifstream ifs(file);
    if(!ifs.is_open())
    {
        cout << "Не удалось открыть файл\n";
        return 1;
    }

    Set *set = new Set(32);
    readSet(ifs, set);
    ifs.close();
    if(strcmp(argv[2], "SETADD") == 0)
    {
        if(argc != 4)
        {
            printHelp();
            return 0;
        }
        set->add(stoi(argv[3]));
        ofstream ofs(file);
        writeSet(ofs, set);
        ofs.close();
    }
    else if(strcmp(argv[2], "SETDEL") == 0)
    {
        if(argc != 4)
        {
            printHelp();
            return 0;
        }
        set->remove(stoi(argv[3]));
        ofstream ofs(file);
        writeSet(ofs, set);
        ofs.close();
    }
    else if(strcmp(argv[2], "SET_AT") == 0)
    {
        if(argc != 4)
        {
            printHelp();
            return 0;
        }
        if(set->contains(stoi(argv[3])))
        {
            cout << "Найдено\n";
        }
        else
        {
            cout << "Не найдено\n";
        }
    }
    else
    {
        cout << "Неизвестная команда\n";
        return 1;
    }
}