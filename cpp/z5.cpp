//var 8

#include <iostream>

struct node
{
    node *l;
    node *r;
    int value;
};

using namespace std;

int main()
{
    node *root = new node;
    int a;
    cin >> a;
    if(a == 0)
        return 0;
    root->value = a;
    cout << "1 ";
    while(1)
    {
        cin >> a;
        if(a == 0)
            break;
        node *x = root;
        node *y = nullptr;
        int height = 1;
        bool exists = false;
        while(x != nullptr)
        {
            if(a == x->value)
            {
                exists = true;
                break;
            }
            y = x;
            if(a < x->value)
                x = x->l;
            else
                x = x->r;
            height++;
        }
        if(!exists)
        {
            node *newNode = new node;
            newNode->value = a;
            if(a < y->value)
                y->l = newNode;
            else
                y->r = newNode;
            printf("%d ", height);
        }
    }
}