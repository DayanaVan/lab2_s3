#include "bstree.h"
#include <iostream>

// Конструктор узла
TreeNode::TreeNode(int key)
{
    this->right = nullptr;
    this->left = nullptr;
    this->key = key;
}

// Конструктор дерева
Tree::Tree()
{
    this->root = nullptr;
}

// Добавление элемента 
void Tree::add(int key)
{
    TreeNode* newNode = new TreeNode(key);
    
    // Если дерево пустое
    if (root == nullptr) {
        root = newNode;
        return;
    }
    
    // Поиск места для вставки
    TreeNode* current = root;
    TreeNode* parent = nullptr;
    
    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            // Элемент уже существует, не добавляем дубликаты
            delete newNode;
            return;
        }
    }
    
    // Вставка нового узла
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

// Поиск элемента 
TreeNode* Tree::search(int key)
{
    TreeNode* current = root;
    
    while (current != nullptr) {
        if (key == current->key) {
            return current;  // Найден
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return nullptr;  // Не найден
}

// Нахождение минимального узла в поддереве
TreeNode* Tree::findMin(TreeNode* node)
{
    if (node == nullptr) return nullptr;
    
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Рекурсивное удаление узла
TreeNode* Tree::removeRec(TreeNode* node, int key)
{
    if (node == nullptr) return nullptr;
    
    if (key < node->key) {
        // Ищем в левом поддереве
        node->left = removeRec(node->left, key);
    } else if (key > node->key) {
        // Ищем в правом поддереве
        node->right = removeRec(node->right, key);
    } else {
        // Узел найден
        TreeNode* temp;
        
        // Случай 1: Узел без детей или с одним ребенком
        if (node->left == nullptr) {
            temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            temp = node->left;
            delete node;
            return temp;
        }
        
        // Случай 2: Узел с двумя детьми
        // Находим минимальный элемент в правом поддереве (преемник)
        temp = findMin(node->right);
        
        // Копируем значение преемника в текущий узел
        node->key = temp->key;
        
        // Удаляем преемника
        node->right = removeRec(node->right, temp->key);
    }
    
    return node;
}

// Удаление элемента
void Tree::remove(int key)
{
    root = removeRec(root, key);
}

// Рекурсивный обход в порядке in-order
void Tree::DFSinRec(std::string &vec, TreeNode *node)
{
    if(node == nullptr)
        return;

    DFSinRec(vec, node->left);
    vec += std::to_string(node->key) + " ";
    DFSinRec(vec, node->right);
}

// Рекурсивный обход в порядке pre-order
void Tree::DFSpreRec(std::string &vec, TreeNode *node)
{
    if (node == nullptr)
        return;

    vec += std::to_string(node->key) + " ";
    DFSpreRec(vec, node->left);
    DFSpreRec(vec, node->right);
}

// Рекурсивный обход в порядке post-order
void Tree::DFSpostRec(std::string &vec, TreeNode *node)
{
    if (node == nullptr)
        return;

    DFSpostRec(vec, node->left);
    DFSpostRec(vec, node->right);
    vec += std::to_string(node->key) + " ";
}

// Обход в ширину (BFS)
void Tree::BFS(std::string &vec)
{
    vec.clear();
    if(this->root == nullptr)
        return;
    
    std::queue<TreeNode*> q;
    q.push(this->root);
    
    while (!q.empty())
    {
        TreeNode* node = q.front();
        q.pop();
        
        if (node != nullptr) {
            vec += std::to_string(node->key) + " ";
            
            // Добавляем детей в очередь, даже если они nullptr
            q.push(node->left);
            q.push(node->right);
        } else {
            vec += "null ";
        }
    }
}

// Вывод дерева в строку
std::string Tree::print()
{
    if(this->root == nullptr)
        return "Дерево пустое\n";
    
    std::string result = "";
    std::string order = "";

    // BFS (по уровням)
    BFS(order);
    result += "Обход в ширину (BFS): " + order + "\n";

    // In-order (сортированный порядок)
    order = "";
    DFSinRec(order, this->root);
    result += "In-order (сортированный): " + order + "\n";

    // Pre-order
    order = "";
    DFSpreRec(order, this->root);
    result += "Pre-order: " + order + "\n";

    // Post-order
    order = "";
    DFSpostRec(order, this->root);
    result += "Post-order: " + order + "\n";
    
    return result;
}
