// Лабораторная работа №5 (2 семестр)
// 
// Дана последовательность операций «добавить вершину», «удалить вершину» и «найти ключ» над бинарным деревом поиска. Выполнить эти операции.
//

#include <iostream>
#include <fstream>
#include <sstream>

struct Tree
{
    int data;
    Tree* left;
    Tree* right;
    Tree* parent;
};

Tree* MAKE(int data, Tree* p)
{
    Tree* q = new Tree;  
    q->data = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}

void ADD(int data, Tree*& root)
{
    if (root == nullptr) {
        root = MAKE(data, nullptr);
        return;
    }
    Tree* v = root;
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
        if (data < v->data)
            v = v->left;
        else
            v = v->right;
    if (data == v->data)
        return;
    Tree* u = MAKE(data, v);
    if (data < v->data)
        v->left = u;
    else
        v->right = u;
}

void PASS(Tree* v)
{
    if (v == nullptr)
        return;

    PASS(v->left);
    std::cout << v->data << std::endl;
    PASS(v->right);
}

Tree* SEARCH(int data, Tree* v)  
{
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
        return SEARCH(data, v->left);
    else
        return SEARCH(data, v->right);
}

int MEASURE(int data, Tree* v)
{
    int deep = 0;
    bool isFinded = false;
    while (v != nullptr)
    {
        deep++;
        if (data == v->data) return deep;
        if (data < v->data) v = v->left;
        else v = v->right;
    }
    return 0;
}

void DELETE(int data, Tree*& root)
{
    Tree* u = SEARCH(data, root);
    if (u == nullptr)
        return;
    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        delete root;
        root = nullptr;
        return;
    }
    if (u->left == nullptr && u->right != nullptr && u == root)
    {
        Tree* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    if (u->left != nullptr && u->right == nullptr && u == root)
    {
        Tree* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    } 
    if (u->left != nullptr && u->right != nullptr)
    {
        Tree* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    Tree* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;
    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;
    if (t != nullptr)
        t->parent = u->parent;
    delete u;
}

void CLEAR(Tree*& v)
{
    if (v == nullptr)
        return;
    CLEAR(v->left);
    CLEAR(v->right);
    delete v;
    v = nullptr;
}

int main()
{
    Tree* root = nullptr;
    std::ifstream in("../input.txt");
    std::ofstream out("../output.txt");

    if (!in.is_open())
    {
        std::cout << "File not found" << std::endl;
        return -1;
    }
    char type;
    int elem;
    while (!in.eof())
    {
        in >> type;
        if (type == 'E') break;
        in >> elem;
        if (type == '+') ADD(elem, root);
        if (type == '-') DELETE(elem, root);
        if (type == '?')
        {
            int deep = MEASURE(elem, root);
            if (deep) out << deep;
            else out << "n";
        }
    }
    CLEAR(root);
    return 0;
}