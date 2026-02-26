#pragma once

#include <string>
#include <queue>

struct TreeNode
{
    TreeNode *right;
    TreeNode *left;
    int key;

    TreeNode(int key);
};

struct Tree
{
    TreeNode *root;

    Tree();

    void add(int key);  // Добавление элемента

    TreeNode* search(int key);  // Поиск элемента

    void remove(int key);  // Удаление элемента

    TreeNode* findMin(TreeNode* node);  // Нахождение минимального узла в поддереве

    TreeNode* removeRec(TreeNode* node, int key);  // Рекурсивное удаление

    std::string print();  // Вывод дерева

    // Вспомогательные методы для вывода
    void DFSinRec(std::string &vec, TreeNode *node);
    void DFSpreRec(std::string &vec, TreeNode *node);
    void DFSpostRec(std::string &vec, TreeNode *node);
    void BFS(std::string &vec);
};
