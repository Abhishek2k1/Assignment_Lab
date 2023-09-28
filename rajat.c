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

void printSet(struct Node *node)
{
    // this function will do in-order traversal recursively
    if (node != NULL)
    {
        printSet(node->left);
        printf("%d ", node->data);
        printSet(node->right);
    }
}

void copyNode(struct Node *node, struct Node **unionRoot)
{
    // This function will printSet and copy node from one bst to another bst
    if (node != NULL)
    {
        copyNode(node->left, unionRoot);
        insert(&*unionRoot, node->data);
        copyNode(node->right, unionRoot);
    }
}

struct Node *unionSet(struct Node *root1, struct Node *root2)
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

void intersection(struct Node *root1, struct Node *root2, struct Node **intersectionRoot)
{
    // This function will do intersection of two set by traversal and search
    if (root1 != NULL)
    {
        intersection(root1->left, root2, intersectionRoot);
        if (search(root2, root1->data))
            insert(&*intersectionRoot, root1->data);
        intersection(root1->right, root2, intersectionRoot);
    }
}

int main()
{
    struct Node *set1Root = NULL, *set2Root = NULL, *unionRoot = NULL, *intersectionRoot = NULL;

    set1Root = createSet("first", set1Root);  // creating first set
    set2Root = createSet("second", set2Root); // creating second set

    printf("\nSet1: ");
    printSet(set1Root);

    printf("\nSet2: ");
    printSet(set2Root);

    unionRoot = unionSet(set1Root, set2Root);
    printf("\nThe union of these two set is: ");
    printSet(unionRoot);

    intersection(set1Root, set2Root, &intersectionRoot);
    printf("\nThe intersection of these two set is: ");
    printSet(intersectionRoot);

    return 0;
}