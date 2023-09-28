#include <iostream>
using namespace std;
// Define a structure for a node in the BST
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    int rank;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to insert a value into a BST
TreeNode *insert(TreeNode *root, int val)
{
    if (root == nullptr)
    {
        return new TreeNode(val);
    }
    root->right = insert(root->right, val);
    return root;
}

// Function to find the root of a set with path compression
TreeNode *findRoot(TreeNode *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->left)
    {
        root->left = findRoot(root->left);
        return root->left;
    }

    return root;
}

// Function to perform Union by Rank
TreeNode *unionSets(TreeNode *set1, TreeNode *set2)
{
    if (set1 == nullptr || set2 == nullptr)
    {
        return (set1 != nullptr) ? set1 : set2;
    }

    TreeNode *root1 = findRoot(set1);
    TreeNode *root2 = findRoot(set2);

    if (root1 == root2)
    {
        return root1; // Sets are already in the same union.
    }

    // Union by rank: Attach the shorter tree to the root of the taller tree.
    if (root1->rank < root2->rank)
    {
        root1->left = root2;
        return root1;
    }
    else if (root1->rank > root2->rank)
    {
        root2->left = root1;
        return root2;
    }
    else
    {
        // If ranks are equal, choose one as the new root and increment its rank.
        root2->left = root1; // Attach root1 as a child of root2
        root2->rank++;       // Increment rank of root2
        return root2;
    }
}

// Function to print the elements of a BST (inorder traversal)
void printSet(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    printSet(root->left);
    cout << root->data << " ";
    printSet(root->right);
}
int main()
{
    TreeNode *set1 = nullptr;
    TreeNode *set2 = nullptr;

    int num_elements1, num_elements2;

    cout << "Enter the number of elements for Set 1: ";
    cin >> num_elements1;
    cout << "Enter the elements for Set 1: ";
    for (int i = 0; i < num_elements1; ++i)
    {
        int val;
        cin >> val;
        set1 = insert(set1, val);
    }

    cout << "Enter the number of elements for Set 2: ";
    cin >> num_elements2;
    cout << "Enter the elements for Set 2: ";
    for (int i = 0; i < num_elements2; ++i)
    {
        int val;
        cin >> val;
        set2 = insert(set2, val);
    }

    // Union operation
    cout << "Set 1: ";
    printSet(set1);
    cout << endl;

    cout << "Set 2: ";
    printSet(set2);
    cout << endl;

    TreeNode *unionResult = unionSets(set1, set2);
    cout << "Union of Set 1 and Set 2: ";
    printSet(unionResult);
    cout << endl;

    return 0;
}