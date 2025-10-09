#include "rbtree.h"

TreeNode::TreeNode(int key, TreeNode *nil)
{
    this->right = nil;
    this->left = nil;
    this->parent = nil;
    this->color = red;
    this->key = key;
}

Tree::Tree()
{
    this->nil = new TreeNode(0, nullptr);
    this->nil->color = black;
    this->root = this->nil;
}

void Tree::leftRotate(TreeNode *x)
{
    TreeNode *y = x->right;
    x->right = y->left;

    if(y->left != this->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == this->nil)
        this->root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;

    x->parent = y;
}

void Tree::rightRotate(TreeNode *x)
{
    TreeNode *y = x->left;
    x->left = y->right;

    if(y->right != this->nil)
        y->right->parent = x;
    y->parent = x->parent;
    if(x->parent == this->nil)
        this->root = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;

    x->parent = y;
}

void Tree::addFix(TreeNode *z)
{
    while(z->parent->color == red)
    {
        if(z->parent == z->parent->parent->left)
        {
            TreeNode *y = z->parent->parent->right;
            if(y->color == red)
            {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else 
            {
                if(z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                rightRotate(z->parent->parent);
            }
        }                
        else
        {
            TreeNode *y = z->parent->parent->left;
            if(y->color == red)
            {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else 
            {
                if(z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                leftRotate(z->parent->parent);
            }
        }
    }
    this->root->color = black;
}

void Tree::add(int key)
{
    TreeNode *z = new TreeNode(key, this->nil);
    TreeNode *y = this->nil;
    TreeNode *x = this->root;
    while(x != this->nil)
    {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if(y == this->nil)
        this->root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = this->nil;
    z->right = this->nil;
    addFix(z);
}

void Tree::transplant(TreeNode *u, TreeNode *v)
{
    if(u->parent == this->nil)
        this->root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

TreeNode *Tree::minimum(TreeNode *x)
{
    while(x->left != this->nil)
        x = x->left;
    return x;
}

void Tree::removeFix(TreeNode *x)
{
    while(x != this->root && x->color == black)
    {
        if(x == x->parent->left)
        {
            TreeNode *w = x->parent->right;
            if(w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == black && w->right->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if(w->right->color == black)
                {
                    w->left->color = black;
                    w->color = red;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                leftRotate(x->parent);
                x = this->root;
            }
        }
        else
        {
            TreeNode *w = x->parent->left;
            if(w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if(w->right->color == black && w->left->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if(w->left->color == black)
                {
                    w->right->color = black;
                    w->color = red;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                rightRotate(x->parent);
                x = this->root;
            }
        }
    }
    x->color = black;
}

void Tree::remove(TreeNode *z)
{
    if(z == this->nil)
        return;
    TreeNode *y = z;
    TreeNode *x = this->nil;
    Color y_origColor = y->color;
    if(z->left == this->nil)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if(z->right == this->nil)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = minimum(z->right);
        y_origColor = y->color;
        x = y->right;
        if(y->parent == z)
            x->parent = y;
        else
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(y_origColor == black)
        removeFix(x);
    delete z;
}

TreeNode *Tree::search(int key)
{
    TreeNode *node = this->root;
    while(node != this->nil && node->key != key)
    {
        if(key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

void Tree::DFSinRec(std::string &vec, TreeNode *node)
{
    if(node == this->nil)
        return;

    DFSinRec(vec, node->left);
    vec += std::to_string(node->key);
    if(node->color == red)
        vec += "_R ";
    else
        vec += "_B ";
    DFSinRec(vec, node->right);
}

void Tree::DFSpreRec(std::string &vec, TreeNode *node)
{
    if (node == this->nil)
        return;

    vec += std::to_string(node->key);
    if(node->color == red)
        vec += "_R ";
    else
        vec += "_B ";
    DFSpreRec(vec, node->left);
    DFSpreRec(vec, node->right);
}

void Tree::DFSpostRec(std::string &vec, TreeNode *node)
{
    if (node == this->nil)
        return;

    DFSpostRec(vec, node->left);
    DFSpostRec(vec, node->right);
    vec += std::to_string(node->key);
    if(node->color == red)
        vec += "_R ";
    else
        vec += "_B ";
}

void Tree::DFSin(std::string &vec)
{
    vec.clear();
    if(this->root == this->nil)
        return;

    DFSinRec(vec, this->root);
}

void Tree::DFSpre(std::string &vec)
{
    vec.clear();
    if(this->root == this->nil)
        return;

    DFSpreRec(vec, this->root);
}

void Tree::DFSpost(std::string &vec)
{
    vec.clear();
    if(this->root == this->nil)
        return;

    DFSpostRec(vec, this->root);
}

void Tree::BFS(std::string &vec)
{
    vec.clear();
    if(this->root == this->nil)
        return;
    
    std::queue<TreeNode*> q;
    q.push(this->root);
    while (!q.empty())
    {
        TreeNode* node = q.front();
        q.pop();
        vec += std::to_string(node->key);
        if(node->color == red)
            vec += "_R ";
        else
            vec += "_B ";
        
        if(node->left != this->nil)
            q.push(node->left);
        if(node->right != this->nil)
            q.push(node->right);
    }
}

std::string Tree::print()
{
    if(this->root == this->nil)
        return "";
    
    std::string a = "";
    std::string order = "";

    BFS(order);
    a += "BFS: " + order + "\n";

    DFSin(order);
    a += "DFS in order: " + order + "\n";

    DFSpost(order);
    a += "DFS post order: " + order + "\n";

    DFSpre(order);
    a += "DFS pre order: " + order + "\n";
    return a;
}