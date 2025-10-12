//var 4 piramida

#include <iostream>
#include <algorithm>

using namespace std;

struct block
{
    int width;
    int height;
};

int main()
{
    int n;
    cin >> n;
    block blocks[n];
    for(int i = 0; i < n; i++)
    {
        cin >> blocks[i].width;
        cin >> blocks[i].height;
    }
    sort(blocks, blocks+n, [](block a, block b) {
        if(a.width != b.width)
        {
            return a.width > b.width;
        }
        else
        {
            return a.height > b.height;
        }
    });
    int resultHeight = blocks[0].height;
    int prevWidth = blocks[0].width;
    for(int i = 1; i < n; i++)
    {
        if(blocks[i].width < prevWidth)
        {
            resultHeight += blocks[i].height;
            prevWidth = blocks[i].width;
        }
    }
    cout << resultHeight << "\n";
}