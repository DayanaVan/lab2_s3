//var 7

#include <iostream>
#include <algorithm>
#include <limits>
#include "stack.h"

using namespace std;

bool checkXML(string& xml)
{
    int tagCount = 0;
    Stack tags;
    for (int i = 0; i < xml.size(); i++)
    {
        if (xml[i] == '<')
        {
            string tag = "";
            bool closes = xml[i + 1] == '/';
            for (int g = i; g < xml.size(); g++)
            {
                if (xml[g] == '>')
                {
                    tag = xml.substr(i + 1 + closes, g - i - 1 - closes);
                    i = g;
                    break;
                }
            }
            if (tag == "")
                return false;
            if (closes)
            {
                string prevTag = tags.pop();
                if (prevTag != tag)
                {
                    return false;
                }
            }
            else
            {
                tags.push(tag);
                tagCount++;
            }
        }
        else if (xml[i] == '>')
            return false;
    }
    return (tags.top == nullptr) && tagCount > 0;
}

int main()
{
    printf("Enter xml line\n");
    string xml;
    getline(cin, xml);
    xml.erase(std::remove_if(xml.begin(), xml.end(), [](char c) {
        return isspace((unsigned int)c);
        }), xml.end());
    if (checkXML(xml))
    {
        cout << "good xml\n";
        return 0;
    }
    for (int i = 0; i < xml.size(); i++)
    {
        string newXml = xml;
        for (char c : "></abcdefghijklmnopqrstuvwxyz")
        {
            if (newXml[i] == c)
                continue;
            newXml[i] = c;
            if (checkXML(newXml))
            {
                printf("change %c at %d to %c\n", xml[i], i, c);
                cout << "new xml: " << newXml << "\n";
                return 0;
            }
        }
    }
    cout << "wrong xml\n";
}