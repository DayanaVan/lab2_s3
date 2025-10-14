//var *
//abracadabra
#include <iostream>
#include "hashtabledouble.h"
#include <unordered_map>

using namespace std;

struct treeNode
{
    treeNode *l;
    treeNode *r;
    int value;
    char c;
};

void deleteTree(treeNode *node)
{
    deleteTree(node->r);
    deleteTree(node->l);
    delete node;
}

void listSort(treeNode *list[], int startIndex, int listSize)
{
    int end = startIndex + listSize;
    for(int i = startIndex; i < end; i++)
    {
        for(int j = startIndex; j < listSize - 1 - i; j++)
        {
            if(list[j]->value > list[j+1]->value)
            {
                swap(list[j], list[j+1]);
            }
        }
    }
}

void generateCodes(unordered_map<char, string> &codes, treeNode* node, string code)
{
    if (node == nullptr)
        return;
    
    if (node->l == nullptr && node->r == nullptr)
    {
        codes[node->c] = code;
        return;
    }
    
    generateCodes(codes, node->l, code + "0");
    generateCodes(codes, node->r, code + "1");
}

string encode(string &input, treeNode *&symbols)
{
    if(input == "")
        return "";
    HashTableDouble *htd = new HashTableDouble(7);
    for(size_t i = 0; i < input.size(); i++)
    {
        if(htd->contains(input[i]))
        {
            htd->insert(input[i], htd->get(input[i]) + 1);
        }
        else
        {
            htd->insert(input[i], 1);
        }
    }
    treeNode** list = new treeNode*[htd->size];
    int listSize = 0;
    for(int i = 0; i < htd->capacity; i++)
    {
        if(htd->table[i] != nullptr && !htd->table[i]->deleted)
        {
            treeNode *tn = new treeNode{nullptr, nullptr, htd->table[i]->value, htd->table[i]->key};
            list[listSize] = tn;
            listSize++;
        }
    }
    delete htd;
    listSort(list, 0, listSize);
    if(symbols != nullptr)
    {
        delete symbols;
    }
    int listOffset = 0;
    while(listSize > 2)
    {
        treeNode *l = list[listOffset];
        treeNode *r = list[listOffset+1];
        list[listOffset+1] = new treeNode{l, r, r->value + l->value, '\0'};
        listOffset++;
        listSize--;
        listSort(list, listOffset, listSize);
    }
    symbols = new treeNode{list[listOffset], list[listOffset+1], 0, '\0'};
    unordered_map<char, string> codes;
    generateCodes(codes, symbols, "");
    string result = "";
    for(char c : input)
    {
        result += codes[c];
    }
    return result;
}

string decode(string &input, treeNode *symbols)
{
    if(input == "")
        return "";

    string result = "";
    treeNode *n = symbols;
    for (char c : input)
    {
        if (c == '0')
        {
            n = n->l;
        }
        else
        {
            n = n->r;
        }
        
        if (n->l == nullptr && n->r == nullptr)
        {
            result += n->c;
            n = symbols;
        }
    }
    return result;
}

void printCodes(unordered_map<char, string> &codes)
{
        cout << "Codes:\n";
        for (auto& pair : codes)
        {
            cout << "'" << pair.first << "' : " << pair.second << endl;
        }
    }

int main()
{
    string input;
    getline(cin, input);
    treeNode *symbols = nullptr;
    string en = encode(input, symbols);
    cout << en << "\n";
    unordered_map<char, string> codes;
    generateCodes(codes, symbols, "");
    printCodes(codes);
    string dec = decode(en, symbols);
    cout << dec << "\n";
}