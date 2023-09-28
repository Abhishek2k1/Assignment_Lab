#include <iostream>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    int rank;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr), rank(0) {}
};

TreeNode *insert(TreeNode *root, int val)
{
    if (root == nullptr)
    {
        return new TreeNode(val);
    }

    if (val < root->data)
    {
        root->left = insert(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = insert(root->right, val);
    }

    return root;
}

TreeNode *findRoot(TreeNode *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    TreeNode *parent = nullptr;
    TreeNode *current = node;

    while (current != nullptr)
    {
        parent = current;
        current = current->left;
    }

    current = node;
    while (current != nullptr)
    {
        TreeNode *next = current->left;
        current->left = parent;
        current = next;
    }

    return parent;
}

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
        return root1;
    }

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
        root2->left = root1;
        root2->rank++;
        return root2;
    }
}

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
