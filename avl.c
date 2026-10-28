#include <stdio.h>
#include <stdlib.h>
/* ---------- Node structure ---------- */
typedef struct Node {
int key;
int height;
struct Node *left;
struct Node *right;
} Node;
/* ---------- Helper functions ---------- */
int height(Node *node)
{
if (node == NULL)
return 0;
return node->height;
}
int max(int a, int b)
{
return (a > b) ? a : b;
}
Node *createNode(int key)
{
Node *newNode = (Node *)malloc(sizeof(Node));
newNode->key = key;
newNode->height = 1; /* a new node is a leaf */
newNode->left = NULL;
newNode->right = NULL;
return newNode;
}
int getBalance(Node *node)
{
if (node == NULL)
return 0;
return height(node->left) - height(node->right);
}
/* ---------- Rotations ---------- */
Node *rightRotate(Node *y) /* LL case */
{
Node *x = y->left;
Node *temp = x->right;
x->right = y; /* perform rotation */
y->left = temp;
y->height = 1 + max(height(y->left), height(y->right));
x->height = 1 + max(height(x->left), height(x->right));
return x; /* new root of subtree */
}
Node *leftRotate(Node *x) /* RR case */
{
Node *y = x->right;
Node *temp = y->left;

y->left = x; /* perform rotation */
x->right = temp;
x->height = 1 + max(height(x->left), height(x->right));
y->height = 1 + max(height(y->left), height(y->right));
return y; /* new root of subtree */
}
/* ---------- Insert ---------- */
Node *insert(Node *root, int key)
{
/* 1. normal BST insertion */
if (root == NULL)
return createNode(key);
if (key < root->key)
root->left = insert(root->left, key);
else if (key > root->key)
root->right = insert(root->right, key);
else
{
printf("Duplicate key not allowed.\n");
return root;
}
/* 2. update height */
root->height = 1 + max(height(root->left), height(root->right));
/* 3. check balance */
int balance = getBalance(root);
/* 4. fix the four cases */
if (balance > 1 && key < root->left->key) /* LL */
return rightRotate(root);
if (balance < -1 && key > root->right->key) /* RR */
return leftRotate(root);
if (balance > 1 && key > root->left->key) /* LR */
{
root->left = leftRotate(root->left);
return rightRotate(root);
}
if (balance < -1 && key < root->right->key) /* RL */
{
root->right = rightRotate(root->right);
return leftRotate(root);
}
return root;
}
/* ---------- Delete ---------- */
Node *minValueNode(Node *node)
{
Node *current = node;
while (current->left != NULL)
current = current->left;
return current;
}

Node *deleteNode(Node *root, int key)
{
/* 1. normal BST deletion */
if (root == NULL)
return root;
if (key < root->key)
root->left = deleteNode(root->left, key);
else if (key > root->key)
root->right = deleteNode(root->right, key);
else
{
if (root->left == NULL || root->right == NULL) /* 0 or 1 child */
{
Node *temp;
if (root->left != NULL)
temp = root->left;
else
temp = root->right;
if (temp == NULL) /* no child */
{
temp = root;
root = NULL;
}
else /* one child */
{
*root = *temp;
}
free(temp);
}
else /* 2 children */
{
Node *temp = minValueNode(root->right); /* inorder successor */
root->key = temp->key;
root->right = deleteNode(root->right, temp->key);
}
}
if (root == NULL)
return root;
/* 2. update height and check balance */
root->height = 1 + max(height(root->left), height(root->right));
int balance = getBalance(root);
/* 3. rebalance (use the child&#39;s balance factor) */
if (balance > 1 && getBalance(root->left) >= 0) /* LL */
return rightRotate(root);
if (balance > 1 && getBalance(root->left) < 0) /* LR */
{
root->left = leftRotate(root->left);
return rightRotate(root);
}
if (balance < -1 && getBalance(root->right) <= 0) /* RR */
return leftRotate(root);
if (balance < -1 && getBalance(root->right) > 0) /* RL */
{
root->right = rightRotate(root->right);

return leftRotate(root);
}
return root;
}
/* ---------- Search and traversals ---------- */
Node *search(Node *root, int key)
{
if (root == NULL || root->key == key)
return root;
if (key < root->key)
return search(root->left, key);
return search(root->right, key);
}
void inorder(Node *root)
{
if (root != NULL)
{
inorder(root->left);
printf("%d ", root->key);
inorder(root->right);
}
}
void preorder(Node *root)
{
if (root != NULL)
{
printf("%d ", root->key);
preorder(root->left);
preorder(root->right);
}
}
/* ---------- Main (menu) ---------- */
int main()
{
Node *root = NULL;
int choice, key;
while (1)
{
printf("\n\n========================\n");
printf(" AVL TREE\n");
printf("========================\n");
printf("1. Insert\n");
printf("2. Delete\n");
printf("3. Search\n");
printf("4. Inorder Traversal\n");
printf("5. Preorder Traversal\n");
printf("6. Exit\n");
printf("========================\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice)
{
case 1:
printf("Enter key to insert: ");
scanf("%d", &key);
root = insert(root, key);

printf("Key inserted successfully.\n");
break;
case 2:
printf("Enter key to delete: ");
scanf("%d", &key);
if (search(root, key) == NULL)
printf("Key not found.\n");
else
{
root = deleteNode(root, key);
printf("Key deleted successfully.\n");
}
break;
case 3:
printf("Enter key to search: ");
scanf("%d", &key);
if (search(root, key) != NULL)
printf("Key found.\n");
else
printf("Key not found.\n");
break;
case 4:
printf("Inorder traversal: ");
inorder(root);
printf("\n");
break;
case 5:
printf("Preorder traversal: ");
preorder(root);
printf("\n");
break;
case 6:
printf("Program terminated.\n");
return 0;
default:
printf("Invalid choice.\n");
}
}   
return 0;
}