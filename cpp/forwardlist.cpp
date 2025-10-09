#include "forwardlist.h"

//node start
ForwardListNode::ForwardListNode(std::string key)
{
    this->key = key;
    this->next = nullptr;
}
//node end

ForwardList::ForwardList()
{
    this->head = nullptr;
}

void ForwardList::insert(std::string key, int index)
{
    if(index == 0)
    {
        addHead(key);
        return;
    }
    
    ForwardListNode *node = this->head;
    for(int i = 0; i < index - 1; i++)
    {
        if(node == nullptr)
            break;
        node = node->next;
    }
    if(node == nullptr)
        return;
    ForwardListNode *newNode = new ForwardListNode(key);
    newNode->next = node->next;
    node->next = newNode;

}

void ForwardList::remove(int index)
{
    if(index == 0)
    {
        removeHead();
        return;
    }

    ForwardListNode *node = this->head;
    for(int i = 0; i < index - 1; i++)
    {
        if(node == nullptr)
            break;
        node = node->next;
    }
    if(node == nullptr)
        return;
    ForwardListNode *toDelete = node->next;
    if(toDelete != nullptr)
    {
        node->next = toDelete->next;
        delete toDelete;
    }
}

void ForwardList::addTail(std::string key)
{
    if(this->head == nullptr)
    {
        this->head = new ForwardListNode(key);
        return;
    }
    ForwardListNode *node = this->head;
    while(node->next != nullptr)
        node = node->next;
    node->next = new ForwardListNode(key);
}

void ForwardList::addHead(std::string key)
{
    if(this->head == nullptr)
    {
        this->head = new ForwardListNode(key);
        return;
    }
    ForwardListNode *node = new ForwardListNode(key);
    node->next = this->head;
    this->head = node;
}

void ForwardList::removeTail()
{
    if(this->head == nullptr)
        return;

    ForwardListNode *node = this->head;
    while(node->next->next != nullptr)
        node = node->next;
    delete node->next;
    node->next = nullptr;
}

void ForwardList::removeHead()
{
    if(this->head == nullptr)
        return;

    ForwardListNode *toDelete = this->head;
    this->head = toDelete->next;
    delete toDelete;
}

std::string ForwardList::printFromHead()
{
    ForwardListNode *node = this->head;
    if(node == nullptr)
        return "";
    std::string a = "";
    while(node->next != nullptr)
    {
        a += node->key + ' ';
        node = node->next;
    }
    a += node->key;
    return a;
}

void ForwardList::printFromTailRec(std::string &s, ForwardListNode *node)
{
    if(node == nullptr)
        return;
    printFromTailRec(s, node->next);
    s += node->key + " ";
}

std::string ForwardList::printFromTail()
{
    std::string s = "";
    printFromTailRec(s, this->head);
    return s;
}

void ForwardList::removeKey(std::string key, int num)
{
    if(num < 0 || this->head == nullptr)
        return;
    int n = 0;
    ForwardListNode *node = this->head;
    if(node->key == key && num == 0)
    {
        removeHead();
        return;
    }
    while(node->next != nullptr)
    {
        if(node->next->key == key)
        {
            if(n == num)
            {
                ForwardListNode *toDelete = node->next;
                node->next = toDelete->next;
                delete toDelete;
                return;
            }
            n++;
        }
        node = node->next;
    }
}

ForwardListNode *ForwardList::find(std::string key, int num)
{
    if(num < 0)
        return nullptr;
    int n = 0;
    ForwardListNode *node = this->head;
    while(node != nullptr)
    {
        if(node->key == key)
        {
            if(n == num)
                return node;
            n++;
        }
        node = node->next;
    }
    return nullptr;
}