#include "list.h"

//node start
ListNode::ListNode(std::string key)
{
    this->key = key;
    this->next = nullptr;
    this->prev = nullptr;
}
//node end

List::List()
{
    this->tail = nullptr;
    this->head = nullptr;
}

void List::insert(std::string key, int index)
{
    if(index == 0)
    {
        addHead(key);
        return;
    }
    
    ListNode *node = this->head;
    for(int i = 0; i < index - 1; i++)
    {
        if(node == nullptr)
            break;
        node = node->next;
    }
    if(node == nullptr)
        return;
    if(node->next == this->tail)
    {
        addTail(key);
        return;
    }
    ListNode *newNode = new ListNode(key);
    newNode->next = node->next;
    newNode->prev = node;
    node->next = newNode;
    newNode->next->prev = node->prev;
}

void List::remove(int index)
{
    if(index == 0)
    {
        removeHead();
        return;
    }

    ListNode *node = this->head;
    for(int i = 0; i < index - 1; i++)
    {
        if(node == nullptr)
            break;
        node = node->next;
    }
    if(node == nullptr)
        return;
    if(node->next == this->tail)
    {
        removeTail();
        return;
    }
    ListNode *toDelete = node->next;
    if(toDelete != nullptr)
    {
        node->next = toDelete->next;
        toDelete->next->prev = node;
        delete toDelete;
    }
}

void List::addTail(std::string key)
{
    ListNode *node = new ListNode(key);
    if(this->tail == nullptr)
    {
        this->tail = node;
        this->head = node;
        return;
    }
    node->prev = this->tail;
    this->tail->next = node;
    this->tail = node;
}

void List::addHead(std::string key)
{
    ListNode *node = new ListNode(key);
    if(this->tail == nullptr)
    {
        this->tail = node;
        this->head = node;
        return;
    }
    node->next = this->head;
    this->head->prev = node;
    this->head = node;
}

void List::removeTail()
{
    if(this->tail == nullptr)
        return;
    if(this->tail == this->head)
    {
        delete this->head;
        this->tail = nullptr;
        this->head = nullptr;
        return;
    }
    this->tail = this->tail->prev;
    delete this->tail->next;
    this->tail->next = nullptr;
}

void List::removeHead()
{
    if(this->head == nullptr)
        return;
    if(this->tail == this->head)
    {
        delete this->tail;
        this->tail = nullptr;
        this->head = nullptr;
        return;
    }
    this->head = this->head->next;
    delete this->head->prev;
    this->head->prev = nullptr;
}

std::string List::printFromHead()
{
    ListNode *node = this->head;
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

std::string List::printFromTail()
{
    ListNode *node = this->tail;
    if(node == nullptr)
        return "";
    std::string a = "";
    while(node->prev != nullptr)
    {
        a += node->key + ' ';
        node = node->prev;
    }
    a += node->key;
    return a;
}

void List::removeKey(std::string key, int num)
{
    if(num < 0)
        return;
    int n = 0;
    ListNode *node = this->head;
    while(node != nullptr)
    {
        if(node->key == key)
        {
            if(n == num)
            {
                if(node == this->tail)
                {
                    removeTail();
                }
                else if(node == this->head)
                {
                    removeHead();
                }
                else
                {
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                    node->next = node->next;
                    delete node;
                }
                return;
            }
            n++;
        }
        node = node->next;
    }
}

ListNode *List::find(std::string key, int num)
{
    if(num < 0)
        return nullptr;
    int n = 0;
    ListNode *node = this->tail;
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