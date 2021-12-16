#include <iostream>
#include <vector>

class Tree
{
public:
    int value;
    Tree *left;
    Tree *right;

    Tree()
    {
        value = 0;
        left = nullptr;
        right = nullptr;
    }

    Tree(int value)
    {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }

    void Add(int value)
    {
        Add(new Tree(value));
    }

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

    void Remove(int value)
    {
        Tree *torem = Find(value);
        Tree *prev = FindPrev(torem);

        if (prev->left == torem)
            prev->left = torem->right;
        else
            prev->right = torem->right;

        std::vector<Tree *> v;
        GetAllFrom(torem->left, v);
        delete torem;

        for (Tree *node : v)
        {
            printf("%p - %d\n", node, node->value);
            Add(node);
        }
    }

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

    Tree *FindPrev(Tree *treenode)
    {
        Tree *current = this;
        if (current == treenode)
            return nullptr;

        while (1)
        {
            if (current->left == treenode || current->right == treenode)
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

    static void GetAllFrom(Tree *from, std::vector<Tree *> &v)
    {
        if (from == nullptr)
            return;
        v.push_back(from);
        GetAllFrom(from->left, v);
        GetAllFrom(from->right, v);
    }

    void Print()
    {
        Tree::Print(this);
    }

#pragma region printing

    static void PrintRelations(Tree *node, int num)
    {
        if (node == nullptr)
        {
            printf("\e[90m<empty>\e[0m\n");
            return;
        }
        printf("\e[1;37m%d\n\e[0;93mleft %d:\e[0m\n", node->value, num);
        PrintRelations(node->left, num + 1);
        printf("\e[93mright %d:\e[0m\n", num);
        PrintRelations(node->right, num + 1);
    }

private:
    typedef struct node
    {
        Tree *address;
        int value;
    } node;
    std::vector<node> nodes;

    int findnode(std::vector<node> &nodes, Tree *address)
    {
        for (int i = 0; i < nodes.size(); i++)
            if (nodes.at(i).address == address)
                return i;
        return -1;
    }

public:
    void Print(Tree *tree)
    {
        std::vector<Tree *> v;
        Tree::GetAllFrom(tree, v);

        for (size_t i = 0; true; i++)
        {
            Tree *current;
            node *last;

            current = i < v.size() ? v.at(i) : nullptr;
            last = i < nodes.size() ? &nodes.at(i) : nullptr;

            if (current == nullptr && last == nullptr)
                break;

            if (findnode(nodes, current) == -1)
            {
                printf("\e[32m%p - %d\e[0m\n", current, current->value);
                nodes.push_back({current, current->value});
            }
            else if (find(v.begin(), v.end(), last->address) == v.end())
            {
                int index = findnode(nodes, last->address);
                printf("\e[31m%p - %d\e[0m\n", last, nodes.at(index).value);
                nodes.erase(nodes.begin() + index);
                i--;
            }
            else
                printf("%p - %d\n", current, current->value);
        }
    }

#pragma endregion
};
