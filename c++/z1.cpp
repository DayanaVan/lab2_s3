#include <iostream>
#include <algorithm>
#include <limits>
#include "stack.h"

using namespace std;

bool checkXML(string& xml)
{
    size_t tagCount = 0;
    // Стек для хранения имен открывающихся тегов
    Stack *tags = new Stack();

    for (size_t i = 0; i < xml.size(); i++)
    {
        if (xml[i] == '<')
        {
            string tag = "";
            bool closes = xml[i + 1] == '/';

            // Поиск закрывающей скобки '>'
            for (size_t g = i; g < xml.size(); g++)
            {
                if (xml[g] == '>')
                {
                    // Извлечение имени тега без < и /
                    tag = xml.substr(i + 1 + closes, g - i - 1 - closes);
                    i = g; // Перемещаем основной указатель
                    break;
                }
            }

            if (tag == "")
                return false; // Ошибка: нет закрывающей скобки

            if (closes)
            {
                // Для закрывающего тега проверяем соответствие последнему открытому
                string prevTag = tags->pop();
                if (prevTag != tag)
                    return false;
            }
            else
            {
                tags->push(tag); // Сохраняем открытый тег
                tagCount++;
            }
        }
        else if (xml[i] == '>')
            return false; // Символ '>' вне тега — ошибка
    }

    bool a = tags->top == nullptr;
    delete tags;
    return a && tagCount > 0; // Корректно, если стек пуст и был хотя бы один тег
}

int main()
{
    printf("Введите xml-строку:\n");

    string xml;
    getline(cin, xml);

    // Удаляем пробельные символы для упрощения проверки
    xml.erase(std::remove_if(xml.begin(), xml.end(), [](char c) {
        return isspace((unsigned int)c);
        }), xml.end());

    if (checkXML(xml))
    {
        cout << "Корректная xml-строка\n";
        return 0;
    }

    // Попытка исправить строку заменой одного символа
    for (size_t i = 0; i < xml.size(); i++)
    {
        string newXml = xml;

        // Перебираем возможные символы для замены
        for (char c : "></abcdefghijklmnopqrstuvwxyz")
        {
            if (newXml[i] == c)
                continue;

            newXml[i] = c; // Замена

            if (checkXML(newXml))
            {
                printf("Меняем %c по индексу %ld на %c\n", xml[i], i, c);
                cout << "Новая xml-строка: " << newXml << "\n";
                return 0;
            }
        }
    }

    cout << "Некорректная xml-строка\n";
    return 0;
}
