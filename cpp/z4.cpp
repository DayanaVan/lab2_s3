//var 4 piramida

#include <iostream>
#include <algorithm>
#include "array.h"

using namespace std;

int main()
{
    int n;
    cin >> n;
    Array *blocks = new Array();
    for(int i = 0; i < n; i++)
    {
        int width, height;
        cin >> width >> height;
        block b{width, height};
        blocks->add(b);
    }
    for(int i = 0; i < blocks->size; i++)
    {
        for(int j = 0; j < blocks->size-1; j++)
        {
            if(blocks->get(j).width < blocks->get(j+1).width)
            {
                swap(blocks->memory[j], blocks->memory[j+1]);
            }
            else if(blocks->get(j).width == blocks->get(j+1).width)
            {
                if(blocks->get(j).height < blocks->get(j+1).height)
                {
                    swap(blocks->memory[j], blocks->memory[j+1]);
                }
            }
        }
    }
    int resultHeight = blocks->get(0).height;
    int prevWidth = blocks->get(0).width;
    for(int i = 1; i < n; i++)
    {
        if(blocks->get(i).width < prevWidth)
        {
            resultHeight += blocks->get(i).height;
            prevWidth = blocks->get(i).width;
        }
    }
    cout << resultHeight << "\n";
}