#include "structures.h"
#include <iostream>
#include "io.h"
#include <cstring>

using namespace std;

void printHelp()
{
    cout << "Usage: ./l1 [FILE] [COMMAND] [ARGUMENTS]\n";
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

    switch(argv[2][0])
    {
        case 'A'://array
        {
            Array *arr = new Array();
            if(readArray(ifs,arr))
            {
                cout << "В файле не массив\n";
                return 1;
            }
            ifs.close();
            if(strcmp(&argv[2][1], "ADD") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                arr->add(argv[3]);
                ofstream ofs(file);
                writeArray(ofs, arr);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "INSERT") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[4];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                arr->add(argv[3], stoi(indexstr));
                ofstream ofs(file);
                writeArray(ofs, arr);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "GET") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                cout << arr->get(stoi(indexstr)) << "\n";
            }
            else if(strcmp(&argv[2][1], "REMOVE") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                arr->remove(stoi(indexstr));
                ofstream ofs(file);
                writeArray(ofs, arr);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "CHANGE") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                arr->change(stoi(indexstr), argv[4]);
                ofstream ofs(file);
                writeArray(ofs, arr);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "SIZE") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << arr->size << "\n";
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << arr->print() << "\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'F'://forward list
        {
            ForwardList *fl = new ForwardList();
            if(readForwardList(ifs,fl))
            {
                cout << "В файле не односвязный список\n";
                return 1;
            }
            ifs.close();
            if(strcmp(&argv[2][1], "ADDTAIL") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                fl->addTail(argv[3]);
                ofstream ofs(file);
                writeForwardList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "ADDHEAD") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                fl->addHead(argv[3]);
                ofstream ofs(file);
                writeForwardList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "INSERT") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[4];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                int index = stoi(indexstr);
                fl->insert(argv[3], index);
                ofstream ofs(file);
                writeForwardList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "REMOVETAIL") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                fl->removeTail();
                ofstream ofs(file);
                writeForwardList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "REMOVEHEAD") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                fl->removeHead();
                ofstream ofs(file);
                writeForwardList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "REMOVEINDEX") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "Индекс - не число\n";
                    return 1;
                }
                int index = stoi(indexstr);
                fl->remove(index);
                ofstream ofs(file);
                writeForwardList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << "С головы: " << fl->printFromHead() << "\n";
                cout << "С хвоста " << fl->printFromTail() << "\n";
            }
            else if(strcmp(&argv[2][1], "REMOVE") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string numstr = argv[4];
                if(!isNumber(numstr))
                {
                    cout << "Значение или номер вхождения - не число\n";
                    return 1;
                }
                fl->removeKey(argv[3], stoi(numstr));                
                ofstream ofs(file);
                writeForwardList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "FIND") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string numstr = argv[4];
                if(!isNumber(numstr))
                {
                    cout << "Значение или номер вхождения - не число\n";
                    return 1;
                }
                auto node = fl->find(argv[3], stoi(numstr));                
                if(node != nullptr)
                    cout << "Найдено\n";
                else
                    cout << "Не найдено\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'L'://list
        {
            List *fl = new List();
            if(readList(ifs,fl))
            {
                cout << "В файле не двусвязный список\n";
                return 1;
            }
            ifs.close();
            if(strcmp(&argv[2][1], "ADDTAIL") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                fl->addTail(argv[3]);
                ofstream ofs(file);
                writeList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "ADDHEAD") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                fl->addHead(argv[3]);
                ofstream ofs(file);
                writeList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "INSERT") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[4];
                if(!isNumber(indexstr))
                {
                    cout << "индекс - не число\n";
                    return 1;
                }
                int index = stoi(indexstr);
                fl->insert(argv[3], index);
                ofstream ofs(file);
                writeList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "REMOVETAIL") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                fl->removeTail();
                ofstream ofs(file);
                writeList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "REMOVEHEAD") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                fl->removeHead();
                ofstream ofs(file);
                writeList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "REMOVEINDEX") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string indexstr = argv[3];
                if(!isNumber(indexstr))
                {
                    cout << "Индекс - не число\n";
                    return 1;
                }
                int index = stoi(indexstr);
                fl->remove(index);
                ofstream ofs(file);
                writeList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << "С головы: " << fl->printFromHead() << "\n";
                cout << "С хвоста " << fl->printFromTail() << "\n";
            }
            else if(strcmp(&argv[2][1], "REMOVE") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string numstr = argv[4];
                if(!isNumber(numstr))
                {
                    cout << "номер вхождения - не число\n";
                    return 1;
                }
                fl->removeKey(argv[3], stoi(numstr));                
                ofstream ofs(file);
                writeList(ofs, fl);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "FIND") == 0)
            {
                if(argc != 5)
                {
                    printHelp();
                    return 0;
                }
                string numstr = argv[4];
                if(!isNumber(numstr))
                {
                    cout << "омер вхождения - не число\n";
                    return 1;
                }
                auto node = fl->find(argv[3], stoi(numstr));                
                if(node != nullptr)
                    cout << "Найдено\n";
                else
                    cout << "Не найдено\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'Q'://queue
        {
            Queue *q = new Queue();
            if(readQueue(ifs,q))
            {
                cout << "В файле не очередь\n";
                return 1;
            }
            ifs.close();
            if(strcmp(&argv[2][1], "PUSH") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                q->push(argv[3]);
                ofstream ofs(file);
                writeQueue(ofs, q);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "POP") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                std::string a = q->pop();
                cout << a << "\n";
                ofstream ofs(file);
                writeQueue(ofs, q);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << "С начала: " << q->print() << "\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'S'://stack
        {
            Stack *s = new Stack();
            if(readStack(ifs,s))
            {
                cout << "В файле не стек\n";
                return 1;
            }
            ifs.close();
            if(strcmp(&argv[2][1], "PUSH") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                s->push(argv[3]);
                ofstream ofs(file);
                writeStack(ofs, s);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "POP") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                std::string a = s->pop();
                cout << a << "\n";
                ofstream ofs(file);
                writeStack(ofs, s);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << "С конца: " << s->print() << "\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        case 'T'://tree
        {
            Tree *t = new Tree();
            if(readTree(ifs,t))
            {
                cout << "В файле не дерево\n";
                return 1;
            }
            ifs.close();
            if(strcmp(&argv[2][1], "ADD") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                if(!isNumber(keystr))
                {
                    cout << "Значение - не число\n";
                    return 1;
                }
                t->add(stoi(keystr));
                ofstream ofs(file);
                writeTree(ofs, t);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "REMOVE") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                if(!isNumber(keystr))
                {
                    cout << "Значение - не число\n";
                    return 1;
                }
                t->remove(t->search(stoi(keystr)));
                ofstream ofs(file);
                writeTree(ofs, t);
                ofs.close();
            }
            else if(strcmp(&argv[2][1], "FIND") == 0)
            {
                if(argc != 4)
                {
                    printHelp();
                    return 0;
                }
                string keystr = argv[3];
                if(!isNumber(keystr))
                {
                    cout << "Значение - не число\n";
                    return 1;
                }
                auto node = t->search(stoi(keystr));
                if(node != t->nil)
                    cout << "Найдено\n";
                else
                    cout << "Не найдено\n";
            }
            else if(strcmp(&argv[2][1], "PRINT") == 0)
            {
                if(argc != 3)
                {
                    printHelp();
                    return 0;
                }
                cout << t->print() << "\n";
            }
            else
            {
                cout << "Неизвестная операция\n";
                return 1;
            }
            break;
        }
        default:
        {
            cout << "Неизвестная структура\n";
            return 1;
        }
    }

    return 0;
}