#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include "bstree.h"

using namespace std;

// Рекурсивный поиск двух неправильных узлов при inorder-обходе
void findSwappedNodes(TreeNode* node, TreeNode*& prev,
                     TreeNode*& first, TreeNode*& second, TreeNode*& middle) {
    if (node == nullptr) return;

    findSwappedNodes(node->left, prev, first, second, middle);

    // Нарушение порядка: prev->key > node->key
    if (prev != nullptr && node->key < prev->key) {
        if (first == nullptr) {
            first = prev;      // Первый нарушитель — предыдущий узел
            middle = node;     // Второй кандидат — текущий
        } else {
            second = node;     // Второй нарушитель найден
        }
    }
    prev = node;

    findSwappedNodes(node->right, prev, first, second, middle);
}

// Восстановление BST путём обмена ключей нарушителей
void recoverTree(Tree& tree) {
    TreeNode *prev = nullptr, *first = nullptr, *second = nullptr, *middle = nullptr;

    findSwappedNodes(tree.root, prev, first, second, middle);

    if (first != nullptr && second != nullptr) {
        swap(first->key, second->key);
        cout << "Исправляем узлы " << first->key << " и " << second->key << endl;
    } else if (first != nullptr && middle != nullptr) {
        swap(first->key, middle->key);
        cout << "Исправляем узлы " << first->key << " и " << middle->key << endl;
    }
}

// Проверка, является ли дерево корректным BST (inorder должен быть отсортирован)
bool isBSTValid(Tree& tree) {
    string inorderStr;
    tree.DFSinRec(inorderStr, tree.root);

    stringstream ss(inorderStr);
    vector<int> inorder;
    int value;
    while (ss >> value) {
        inorder.push_back(value);
    }

    for (size_t i = 1; i < inorder.size(); i++) {
        if (inorder[i] < inorder[i-1]) return false;
    }
    return true;
}

int main() {
    Tree tree;

    // Ввод чисел для построения дерева
    cout << "Введите числа для построения дерева (завершите любой буквой): ";
    vector<int> values;
    int value;
    while (cin >> value) {
        values.push_back(value);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (values.empty()) {
        cout << "Не введено ни одного числа.\n";
        return 1;
    }

    // Построение корректного BST
    for (int val : values) {
        tree.add(val);
    }

    // Ввод двух чисел, которые нужно поменять местами (искусственное нарушение)
    cout << "Введите два числа, которые нужно поменять местами: ";
    int val1, val2;
    if (!(cin >> val1 >> val2)) {
        cout << "Ошибка ввода.\n";
        return 1;
    }

    TreeNode* node1 = tree.search(val1);
    TreeNode* node2 = tree.search(val2);

    if (node1 != nullptr && node2 != nullptr) {
        // Меняем значения, создавая ошибку
        node1->key = val2;
        node2->key = val1;
    } else {
        cout << "Один или оба узла не найдены в дереве.\n";
        return 1;
    }

    cout << "\nДерево\n";
    cout << tree.print();

    // Проверка и восстановление
    if (isBSTValid(tree)) {
        cout << "Дерево является корректным.\n";
    } else {
        cout << "Обнаружена ошибка.\n\n";
        recoverTree(tree);
        cout << "\nВосстановленное дерево\n";
        cout << tree.print();
        if (isBSTValid(tree)) {
            cout << "Дерево успешно восстановлено.\n";
        } else {
            cout << "Ошибка при восстановлении дерева!\n";
        }
    }

    return 0;
}
