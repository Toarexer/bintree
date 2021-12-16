#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#include <iostream>
#include <vector>

class Tree
{
public:
    int value;
    Tree *left;
    Tree *right;

    // Create a new root node.
    Tree()
    {
        value = 0;
        left = nullptr;
        right = nullptr;
    }

    // Create a new root node.
    Tree(int value)
    {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }

    // Add a new node to the Tree.
    void Add(int value)
    {
        Add(new Tree(value));
    }

    // Add a new node to the Tree.
    void Add(Tree *newnode)
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
                else
                    current = current->left;
            }
            else
            {
                if (current->right == nullptr)
                {
                    current->right = newnode;
                    return;
                }
                else
                    current = current->right;
            }
    }

    // Remove a node from the Tree.
    void Remove(int value)
    {
        Remove(Find(value));
    }

    // Remove a node from the Tree.
    void Remove(Tree *node)
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
        {
            printf("%p - %d\n", n, n->value);
            Add(n);
        }
    }

    // Return the first node with matching value or nullptr if no matching node is found.
    Tree *Find(int value)
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

    // Return the node before the selected node.
    // If the node does not exist or if it is the root nullptr is returned.
    Tree *FindPrev(Tree *node)
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

    // Get all nodes from a Tree.
    static void GetAllElements(Tree *firstnode, std::vector<Tree *> &v)
    {
        if (firstnode == nullptr)
            return;
        v.push_back(firstnode);
        GetAllElements(firstnode->left, v);
        GetAllElements(firstnode->right, v);
    }

#pragma region Printing
private:
    static BOOL SetConsoleColor(WORD wAttributes)
    {
        return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes);
    }

public:
    // Print out the tree from the selected node.
    // The num specifes the startign number to mark the tree levels.
    static void PrintTree(Tree *node, int num)
    {
        PrintNode(node, num, '\0');
    }

    static void PrintNode(Tree *node, int num, char c)
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

private:
    typedef struct node
    {
        Tree *address;
        int value;
    } node;
    std::vector<node> nodes;

    static int findnode(std::vector<node> &nodes, Tree *address)
    {
        for (int i = 0; i < nodes.size(); i++)
            if (nodes.at(i).address == address)
                return i;
        return -1;
    }

public:
    // Print out changes in the tree since the last Print.
    // Bug: Too many removes between prints can lead to skipped elements.
    void Print()
    {
        Print(this);
    }

    // Print out changes in the tree since the last Print.
    // Bug: Too many removes between prints can lead to skipped elements.
    static void Print(Tree *tree)
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
            else if (find(v.begin(), v.end(), last->address) == v.end())
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

#pragma endregion
};
