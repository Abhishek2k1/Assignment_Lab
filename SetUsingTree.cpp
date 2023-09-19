#include <iostream>

class TreeNode
{
public:
    int key;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data)
    {
        key = data;
        left = nullptr;
        right = nullptr;
    }
};

class TreeSet
{
private:
    TreeNode *root;

public:
    TreeSet()
    {
        root = nullptr;
    }

    void insert(int key)
    {
        root = insertRec(root, key);
    }

    bool search(int key)
    {
        return searchRec(root, key);
    }

    TreeSet unionSet(const TreeSet &otherSet)
    {
        TreeSet result;
        unionRec(root, result);
        unionRec(otherSet.root, result);
        return result;
    }

    TreeSet intersectionSet(const TreeSet &otherSet)
    {
        TreeSet result;
        intersectionRec(root, otherSet, result);
        return result;
    }

private:
    TreeNode *insertRec(TreeNode *node, int key)
    {
        if (node == nullptr)
        {
            return new TreeNode(key);
        }

        if (key < node->key)
        {
            node->left = insertRec(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insertRec(node->right, key);
        }

        return node;
    }

    bool searchRec(TreeNode *node, int key)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (key == node->key)
        {
            return true;
        }
        else if (key < node->key)
        {
            return searchRec(node->left, key);
        }
        else
        {
            return searchRec(node->right, key);
        }
    }

    void unionRec(TreeNode *node, TreeSet &result)
    {
        if (node != nullptr)
        {
            result.insert(node->key);
            unionRec(node->left, result);
            unionRec(node->right, result);
        }
    }

    void intersectionRec(TreeNode *node, const TreeSet &otherSet, TreeSet &result)
    {
        if (node != nullptr)
        {
            if (otherSet.search(node->key))
            {
                result.insert(node->key);
            }
            intersectionRec(node->left, otherSet, result);
            intersectionRec(node->right, otherSet, result);
        }
    }
};

int main()
{
    TreeSet set1;
    int n, val;

    std::cout << "Enter the number of elements for Set 1: ";
    std::cin >> n;

    std::cout << "Enter elements for Set 1: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> val;
        set1.insert(val);
    }

    TreeSet set2;

    std::cout << "Enter the number of elements for Set 2: ";
    std::cin >> n;

    std::cout << "Enter elements for Set 2: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> val;
        set2.insert(val);
    }

    TreeSet unionSet = set1.unionSet(set2);
    TreeSet intersectionSet = set1.intersectionSet(set2);

    std::cout << "Set 1: ";
    for (int i = 1; i <= 10; i++)
    {
        std::cout << " " << (set1.search(i) ? i : 0);
    }
    std::cout << std::endl;

    std::cout << "Set 2: ";
    for (int i = 1; i <= 10; i++)
    {
        std::cout << " " << (set2.search(i) ? i : 0);
    }
    std::cout << std::endl;

    std::cout << "Union Set: ";
    for (int i = 1; i <= 10; i++)
    {
        std::cout << " " << (unionSet.search(i) ? i : 0);
    }
    std::cout << std::endl;

    std::cout << "Intersection Set: ";
    for (int i = 1; i <= 10; i++)
    {
        std::cout << " " << (intersectionSet.search(i) ? i : 0);
    }
    std::cout << std::endl;

    return 0;
}