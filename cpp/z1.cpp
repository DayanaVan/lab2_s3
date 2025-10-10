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
    printf("Enter xml line\n");
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
            bool closes = line[i+1] == '/';
            for(int g = i; g < line.size(); g++)
            {
                if(line[g] == '>')
                {
                    tag = line.substr(i+1+closes, g-i-1-closes);
                    break;
                }
            }
            printf("debug tag: %s\n",tag.c_str());   
            if(closes)
            {
                string prevTag = tags->pop();
                if(prevTag != tag)
                {
                    //bad
                    cout << "bad xml\n";
                    return 0;
                }
            }
            else//opens
            {
                tags->push(tag);
            }
        }
        if(line[i] == '>')//previous > is bullshit or this one
        {
            
        }
    }
    if(tags->top != nullptr)
    {
        printf("bad xml\n");
        return 0;
    }
    printf("final xml: %s", line.c_str());
}