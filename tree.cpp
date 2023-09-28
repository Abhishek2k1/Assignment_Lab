#include <iostream>
#include <cstdlib>

// Define a binary tree node structure
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Set
{
private:
    TreeNode *root;

    // Helper function to insert a value into the BST
    TreeNode *insert(TreeNode *node, int data)
    {
        if (node == nullptr)
        {
            return new TreeNode(data);
        }

        if (data < node->data)
        {
            node->left = insert(node->left, data);
        }
        else if (data > node->data)
        {
            node->right = insert(node->right, data);
        }

        return node;
    }

    // Helper function to perform an inorder traversal
    void inorderTraversal(TreeNode *node)
    {
        if (node)
        {
            inorderTraversal(node->left);
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    // Helper function to perform the union of two sets
    TreeNode *setUnion(TreeNode *root1, TreeNode *root2)
    {
        if (root1 == nullptr)
        {
            return root2;
        }
        if (root2 == nullptr)
        {
            return root1;
        }

        TreeNode *result = nullptr;
        result = insert(result, root1->data);
        result = setUnion(result, root1->left);
        result = setUnion(result, root1->right);
        result = setUnion(result, root2);

        return result;
    }

    // Helper function to perform the intersection of two sets
    TreeNode *setIntersection(TreeNode *root1, TreeNode *root2)
    {
        if (root1 == nullptr || root2 == nullptr)
        {
            return nullptr;
        }

        TreeNode *result = nullptr;

        if (root1->data < root2->data)
        {
            result = setIntersection(root1->right, root2);
        }
        else if (root1->data > root2->data)
        {
            result = setIntersection(root1, root2->right);
        }
        else
        {
            result = insert(result, root1->data);
            result = setIntersection(root1->left, root2->left);
            result = setIntersection(root1->right, root2->right);
        }

        return result;
    }

public:
    Set() : root(nullptr) {}

    // Function to insert a value into the set
    void insert(int data)
    {
        root = insert(root, data);
    }

    // Function to perform the union of two sets
    Set setUnion(Set &set2)
    {
        Set resultSet;
        resultSet.root = setUnion(root, set2.root);
        return resultSet;
    }

    // Function to perform the intersection of two sets
    Set setIntersection(Set &set2)
    {
        Set resultSet;
        resultSet.root = setIntersection(root, set2.root);
        return resultSet;
    }

    // Function to display the elements in the set
    void display()
    {
        inorderTraversal(root);
        std::cout << std::endl;
    }
};

int main()
{
    Set set1, set2;

    int n, data;

    std::cout << "Enter the number of elements in Set 1: ";
    std::cin >> n;
    std::cout << "Enter the elements of Set 1: ";
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data;
        set1.insert(data);
    }

    std::cout << "Enter the number of elements in Set 2: ";
    std::cin >> n;
    std::cout << "Enter the elements of Set 2: ";
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data;
        set2.insert(data);
    }

    Set unionSet = set1.setUnion(set2);
    Set intersectionSet = set1.setIntersection(set2);

    std::cout << "Union of Set 1 and Set 2: ";
    unionSet.display();

    std::cout << "Intersection of Set 1 and Set 2: ";
    intersectionSet.display();

    return 0;
}
