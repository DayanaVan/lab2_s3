//var 7 xml parser

//random / > <
//forgot / > <
//random > < inside of tag

#include <iostream>
#include <algorithm>
#include "stack.h"

using namespace std;

int main()
{
    cout << "Enter xml line\n";
    string line;
    getline(cin, line);
    line.erase(std::remove_if(line.begin(), line.end(), [](char c) {
        return isspace((unsigned int)c);
    }), line.end());
    Stack *tags = new Stack;
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == '<')
        {
            string tag = "";
            bool opens = line[i+1] != '/';
            
            cout << "debug tag: " << tag << "\n";
            if(opens)
            {
                tags->push(tag);
            }
            else
            {
                string prevTag = tags->pop();
                if(prevTag != tag)
                {
                    //bad
                    cout << "bad xml\n";
                    return 0;
                }
            }
        }
        if(line[i] == '>')//previous > is bullshit or this one
        {
            
        }
    }
    if(tags->top != nullptr)
    {
        cout << "bad xml\n";
    }
}