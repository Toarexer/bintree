#include <iostream>
#include <algorithm>
#include "tree.h"

#define p         \
    tree.Print(); \
    putchar('\n')

int main()
{
    Tree tree = Tree(12);

    tree.Add(5);
    p;
    tree.Add(7);
    p;
    tree.Add(23);
    tree.Add(45);
    tree.Add(69);
    p;
    tree.Remove(45);
    p;
    tree.Add(14);
    tree.Add(33);
    tree.Add(10);
    tree.Remove(23);
    p;
    tree.Add(22);
    tree.Remove(22);
    p;
    tree.Add(53);
    tree.Add(2);
    tree.Add(9);
    tree.Print();

    putchar('\n');
    Tree::PrintTree(&tree, 0);
    printf("\nCount: %d\n", tree.Count());
    getchar();
}
