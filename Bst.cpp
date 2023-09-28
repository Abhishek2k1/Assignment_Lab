#include <iostream>
#include <set>

// Define the structure for a TreeNode
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Insert a new node into the BST
TreeNode *insert(TreeNode *root, int data)
{
    if (root == nullptr)
    {
        return new TreeNode(data);
    }
    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    return root;
}

// Print the elements of the BST in-order
void printInOrder(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    printInOrder(root->left);
    std::cout << root->data << " ";
    printInOrder(root->right);
}

// Perform the union of two BST sets
TreeNode *unionBST(TreeNode *set1, TreeNode *set2)
{
    if (set1 == nullptr)
        return set2;
    if (set2 == nullptr)
        return set1;

    TreeNode *result = nullptr;
    std::set<int> elements;

    // Insert elements from the first set into the result tree
    // and also add them to the set to avoid duplicates
    TreeNode *current = set1;
    while (current != nullptr)
    {
        result = insert(result, current->data);
        elements.insert(current->data);
        current = current->right;
    }

    // Insert elements from the second set into the result tree
    // but skip elements that are already in the set
    current = set2;
    while (current != nullptr)
    {
        if (elements.find(current->data) == elements.end())
        {
            result = insert(result, current->data);
        }
        current = current->right;
    }

    return result;
}

// Perform the intersection of two BST sets
TreeNode *intersectionBST(TreeNode *set1, TreeNode *set2)
{
    if (set1 == nullptr || set2 == nullptr)
        return nullptr;

    TreeNode *result = nullptr;

    std::set<int> elements;
    TreeNode *current = set1;

    // Insert all elements from the first set into the set
    while (current != nullptr)
    {
        elements.insert(current->data);
        current = current->right;
    }

    // Traverse the second set and insert common elements into the result tree
    current = set2;
    while (current != nullptr)
    {
        if (elements.find(current->data) != elements.end())
        {
            result = insert(result, current->data);
        }
        current = current->right;
    }

    return result;
}

int main()
{
    TreeNode *set1 = nullptr; // First set
    TreeNode *set2 = nullptr; // Second set

    int n;
    std::cout << "Enter the number of elements in the first set: ";
    std::cin >> n;

    std::cout << "Enter " << n << " elements for the first set:\n";
    for (int i = 0; i < n; ++i)
    {
        int data;
        std::cin >> data;
        set1 = insert(set1, data);
    }

    std::cout << "Enter the number of elements in the second set: ";
    std::cin >> n;

    std::cout << "Enter " << n << " elements for the second set:\n";
    for (int i = 0; i < n; ++i)
    {
        int data;
        std::cin >> data;
        set2 = insert(set2, data);
    }

    std::cout << "First set elements (in-order): ";
    printInOrder(set1);
    std::cout << std::endl;

    std::cout << "Second set elements (in-order): ";
    printInOrder(set2);
    std::cout << std::endl;

    TreeNode *unionResult = unionBST(set1, set2);
    std::cout << "Union of sets (in-order): ";
    printInOrder(unionResult);
    std::cout << std::endl;

    TreeNode *intersectionResult = intersectionBST(set1, set2);
    std::cout << "Intersection of sets (in-order): ";
    printInOrder(intersectionResult);
    std::cout << std::endl;

    // Clean up the BSTs (deallocating memory)
    // This part is usually implemented with a destructor
    // but for simplicity, we are not covering it here.

    return 0;
}
