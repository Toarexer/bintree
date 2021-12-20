#pragma once
#include <vector>

#ifdef BINTREE_LIB
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

class DECLSPEC Tree
{
public:
    int value;
    Tree *left;
    Tree *right;

    // Creates a new root node.
    Tree();

    // Creates a new root node.
    Tree(int value);

    // Adds a new node to the Tree.
    void Add(int value);

    // Adds a new node to the Tree.
    void Add(Tree *newnode);

    // Removes a node from the Tree.
    void Remove(int value);

    // Removes a node from the Tree.
    void Remove(Tree *node);

    // Returns the first node with matching value or nullptr if no matching node is found.
    Tree *Find(int value);

    // Returns the node before the selected node.
    // If the node does not exist or if it is the root nullptr is returned.
    Tree *FindPrev(Tree *node);

    // Returns the number of nodes.
    int Count();

    // Returns the number of nodes starting from the specfied one.
    static int CountFrom(Tree *node);

    // Returns the node with the bigest value.
    Tree *GetBigest();

    // Returns the node with the smallest value.
    Tree *GetSmallest();

    // Get all nodes from a Tree.
    static void GetAllElements(Tree *firstnode, std::vector<Tree *> &v);

    // Prints out the tree starting from the selected node.
    // The num specifes the starting number to mark the tree levels.
    static void PrintTree(Tree *node, int num);

    static void PrintNode(Tree *node, int num, char c);

    // Prints out changes in the tree since the last Print.
    void Print();

    // Prints out changes in the tree since the last Print.
    static void Print(Tree *tree);

    typedef struct node
    {
        Tree *address;
        int value;
    } node;
    std::vector<node> nodes;
};
