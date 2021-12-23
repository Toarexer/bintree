#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#include <iostream>
#include <vector>

#define BINTREE_LIB
#include "bintreelib.h"

Tree::Tree() : value(0), left(nullptr), right(nullptr) {}

Tree::Tree(int value) : value(value), left(nullptr), right(nullptr) {}

void Tree::Add(int value)
{
    Add(new Tree(value));
}

void Tree::Add(Tree *newnode)
{
    Tree *current = this;

    while (1)
        if (newnode->value < current->value)
        {
            if (current->left == nullptr)
            {
                current->left = newnode;
                return;
            }
            current = current->left;
        }
        else
        {
            if (current->right == nullptr)
            {
                current->right = newnode;
                return;
            }
            current = current->right;
        }
}

void Tree::Remove(int value)
{
    Remove(Find(value));
}

void Tree::Remove(Tree *node)
{
    Tree *torem = node;
    Tree *prev = FindPrev(torem);

    if (prev->left == torem)
        prev->left = torem->right;
    else
        prev->right = torem->right;

    std::vector<Tree *> v;
    GetAllElements(torem->left, v);
    delete torem;

    for (Tree *n : v)
        Add(n);
}

Tree *Tree::Find(int value)
{
    Tree *current = this;

    while (1)
        if (current->value == value)
            return current;
        else if (value < current->value)
        {
            if (current->left == nullptr)
                return nullptr;
            current = current->left;
        }
        else
        {
            if (current->right == nullptr)
                return nullptr;
            current = current->right;
        }
}

Tree *Tree::FindPrev(Tree *node)
{
    Tree *current = this;
    if (current == node)
        return nullptr;

    while (1)
    {
        if (current->left == node || current->right == node)
            return current;
        if (value < current->value)
        {
            if (current->left == nullptr)
                return nullptr;
            else
                current = current->left;
        }
        else
        {
            if (current->right == nullptr)
                return nullptr;
            else
                current = current->right;
        }
    }
}

int Tree::Count()
{
    return CountFrom(this);
}

int Tree::CountFrom(Tree *node)
{
    if (node == nullptr)
        return 0;
    return 1 + CountFrom(node->left) + CountFrom(node->right);
}

Tree *Tree::GetBigest()
{
    Tree *current = this;
    while (current != nullptr)
        current = current->right;
    return current;
}

Tree *Tree::GetSmallest()
{
    Tree *current = this;
    while (current != nullptr)
        current = current->left;
    return current;
}

void Tree::GetAllElements(Tree *firstnode, std::vector<Tree *> &v)
{
    if (firstnode == nullptr)
        return;
    v.push_back(firstnode);
    GetAllElements(firstnode->left, v);
    GetAllElements(firstnode->right, v);
}

static BOOL SetConsoleColor(WORD wAttributes)
{
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes);
}

void Tree::PrintTree(Tree *node, int num)
{
    PrintNode(node, num, '\0');
}

void Tree::PrintNode(Tree *node, int num, char c)
{
    if (node == nullptr)
        return;
    for (int i = 0; i < num; i++)
        putchar('\t');

    SetConsoleColor(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    if (c == '\0')
        printf("%c 0:", 204);
    else
        printf("%c %c%d:", 192, c, num);
    printf(" %d %c ", node->value, 26);
    SetConsoleColor(FOREGROUND_INTENSITY);
    if (node->left == nullptr)
        printf("l: <empty> ");
    else
        printf("l: %d ", node->left->value);

    if (node->right == nullptr)
        printf("r: <empty>");
    else
        printf("r: %d", node->right->value);
    SetConsoleColor(FOREGROUND_WHITE);
    putchar('\n');

    PrintNode(node->left, num + 1, 'l');
    PrintNode(node->right, num + 1, 'r');
}

int findnode(std::vector<Tree::node> &nodes, Tree *address)
{
    for (int i = 0; i < nodes.size(); i++)
        if (nodes.at(i).address == address)
            return i;
    return -1;
}

bool containsaddr(Tree *addr, std::vector<Tree *> &v)
{
    for (Tree *a : v)
        if (addr == a)
            return true;
    return false;
}

void Tree::Print()
{
    Print(this);
}

void Tree::Print(Tree *tree)
{
    std::vector<Tree *> v;
    GetAllElements(tree, v);

    for (size_t i = 0; true; i++)
    {
        Tree *current;
        node *last;

        current = i < v.size() ? v.at(i) : nullptr;
        last = i < tree->nodes.size() ? &(tree->nodes).at(i) : nullptr;

        if (current == nullptr && last == nullptr)
            break;

        if (findnode(tree->nodes, current) == -1 && current != nullptr)
        {
            SetConsoleColor(FOREGROUND_GREEN);
            printf("%p - %d\n", current, current->value);
            SetConsoleColor(FOREGROUND_WHITE);
            tree->nodes.push_back({current, current->value});
        }
        else if (!containsaddr(last->address, v))
        {
            int index = findnode(tree->nodes, last->address);
            SetConsoleColor(FOREGROUND_RED);
            printf("%p - %d\n", last, tree->nodes.at(index).value);
            SetConsoleColor(FOREGROUND_WHITE);
            tree->nodes.erase(tree->nodes.begin() + index);
            i--;
        }
        else if (current != nullptr)
            printf("%p - %d\n", current, current->value);
    }
}
