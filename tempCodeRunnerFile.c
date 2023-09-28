#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *left;
    int data;
    struct Node *right;
};

void insert(struct Node **node, int data)
{
    // this function will insert the element for a BST
    if (*node != NULL)
    {
        if (data > (*node)->data)
            insert(&((*node)->right), data);
        else if (data < (*node)->data)
            insert(&((*node)->left), data);
    }
    else
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // dynamically allocated memory for a node
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        *node = newNode;
    }
}

struct Node *createSet(char *setName, struct Node *root)
{
    // this function will create a set for n elements
    int n, data;
    printf("\nCreate %s set\nEnter the size of the %s set: ", setName, setName);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter the %d no value: ", i + 1);
        scanf("%d", &data);
        insert(&root, data);
    }
    printf("Set created!\n");
    return root;
}

void traverse(struct Node *node)
{
    // this function will do in-order traversal recursively
    if (node != NULL)
    {
        traverse(node->left);
        printf("%d ", node->data);
        traverse(node->right);
    }
}

void copyNode(struct Node *node, struct Node **unionRoot)
{
    // This function will traverse and copy node from one bst to another bst
    if (node != NULL)
    {
        copyNode(node->left, unionRoot);
        insert(&*unionRoot, node->data);
        copyNode(node->right, unionRoot);
    }
}

struct Node *unionOfTwoSets(struct Node *root1, struct Node *root2)
{
    // This function will do union of two set by calling copy node that follow bst rule
    struct Node *unionRoot = NULL;
    copyNode(root1, &unionRoot);
    copyNode(root2, &unionRoot);
    return unionRoot;
}

int search(struct Node *root, int data)
{
    // This function will search the data in BST
    if (root == NULL)
        return 0;
    if (data == root->data)
        return 1;
    if (data < root->data)
        return search(root->left, data);
    return search(root->right, data);
}

void intersectionOfTwoSets(struct Node *root1, struct Node *root2, struct Node **intersectionRoot)
{
    // This function will do intersection of two set by traversal and search
    if (root1 != NULL)
    {
        intersectionOfTwoSets(root1->left, root2, intersectionRoot);
        if (search(root2, root1->data))
            insert(&*intersectionRoot, root1->data);
        intersectionOfTwoSets(root1->right, root2, intersectionRoot);
    }
}

int main()
{
    struct Node *set1Root = NULL, *set2Root = NULL, *unionRoot = NULL, *intersectionRoot = NULL;

    set1Root = createSet("first", set1Root);  // creating first set
    set2Root = createSet("second", set2Root); // creating second set

    printf("\nThe first set is:\n");
    traverse(set1Root);

    printf("\nThe second set is:\n");
    traverse(set2Root);

    unionRoot = unionOfTwoSets(set1Root, set2Root);
    printf("\n\nThe union of these two set is:\n");
    traverse(unionRoot);

    intersectionOfTwoSets(set1Root, set2Root, &intersectionRoot);
    printf("\n\nThe intersection of these two set is:\n");
    traverse(intersectionRoot);

    return 0;
}