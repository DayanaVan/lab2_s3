#pragma once

#include <string>
#include <queue>
#include <vector>

#define Color bool
#define red true
#define black false

struct TreeNode
{
    TreeNode *right;
    TreeNode *left;
    TreeNode *parent;
    Color color;
    int key;

    TreeNode(int key, TreeNode *nil);
};

struct Tree
{
    TreeNode *root;
    TreeNode *nil;

    Tree();

    void leftRotate(TreeNode *x);

    void rightRotate(TreeNode *x);

    void addFix(TreeNode *node);

    void add(int key);

    void transplant(TreeNode *u, TreeNode *v);

    void removeFix(TreeNode *node);

    void remove(TreeNode *z);

    TreeNode *minimum(TreeNode *x);

    TreeNode *search(int key);

    void DFSin(std::string &vec);

    void DFSpre(std::string &vec);

    void DFSpost(std::string &vec);

    void DFSinRec(std::string &vec, TreeNode *node);

    void DFSpreRec(std::string &vec, TreeNode *node);

    void DFSpostRec(std::string &vec, TreeNode *node);

    void BFS(std::string &vec);

    std::string print();
};