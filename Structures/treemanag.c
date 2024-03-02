#include <stdio.h>
#include <stdlib.h>

typedef struct treenode *Treeptr;

struct treenode {
    int data;
    Treeptr left;
    Treeptr right;
};

Treeptr addtree(Treeptr p, int x) { //Δυαδικό δενδρο αναζητησης
    if(p == NULL) {
        Treeptr newnode = malloc(sizeof(struct treenode));
        newnode->data = x;
        newnode->right = newnode->left = NULL;
        return newnode;
    }
    if(p->data > x) {
        p->left = addtree(p->left, x);
    }else if(p->data < x ) {
        p->right = addtree(p->right, x);
    }
    return p;
}

int empty(Treeptr t) {
    return t == NULL;
}

int depth(Treeptr t) {
    if(t == NULL) {
        return -1;
    }
    int left = depth(t->left);
    int right = depth(t->right);
    return 1 + ((left > right) ? left : right);
}

void preorder(Treeptr t) { //Τυπωνει πρωτα αριστερα και μετα δεξιά.
    if(t==NULL) return;
    printf("%d ",t->data);
    preorder(t->left);
    preorder(t->right);
   
   return;
}

void inorder(Treeptr t) { //Τυπωνει πρώτα τον αριστερό κόμβο, μετά τον τρέχοντα και τέλος τον δεξιό
    if(t==NULL) return;
    inorder(t->left);
    printf("%d ",t->data);
    inorder(t->right);
   
   return;
}

void postorder(Treeptr t) { //Τυπωνει πρώτα τους κόμβους παιδιά και στο τέλος τον τρέχοντα κόμβο
    if(t==NULL) return;
    postorder(t->left);
    postorder(t->right);
    printf("%d ",t->data);
   
   return;
}

void myfun(Treeptr p)
{ int lv = 0;
while (pl(p, lv)){
lv++;
}
}

int pl(Treeptr p, int lv)
{ if (p == NULL) return 0;
if (!lv) {
fprintf(stderr,"%d ",p->data);
return 1;
}
return (pl(p->left, lv-1) | pl(p->right, lv-1));
}


Treeptr deleteNode(Treeptr root, int k)
{
    // Base case
    if (root == NULL)
        return root;
 
    // Recursive calls for ancestors of
    // node to be deleted
    if (root->data > k) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->data < k) {
        root->right = deleteNode(root->right, k);
        return root;
    }
 
    // We reach here when root is the node
    // to be deleted.
 
    // If one of the children is empty
    if (root->left == NULL) {
        Treeptr temp = root->right;
        free(root);
        return temp;
    }
    else if (root->right == NULL) {
        Treeptr temp = root->left;
        free(root);
        return temp;
    }
 
    // If both children exist
    else {
 
        Treeptr succParent = root;
 
        // Find successor
        Treeptr succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }
 
        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
 
        // Copy Successor Data to root
        root->data = succ->data;
 
        // Delete Successor and return root
        free(succ);
        return root;
    }
}

int exists(Treeptr t, int value) {
 if (t == NULL) 
    return 0;
 if (t->data == value)
    return 1;
 if (value < t->data)
    return exists(t->left, value);

    return exists(t->right, value);
}


void deleteTree(Treeptr node) 
{
    if (node == NULL) return;

    /* first delete both subtrees */
    deleteTree(node->left);
    deleteTree(node->right);
  
    /* then delete the node */
    //printf("\n Deleting node: %d", node->data);
    free(node);
} 




int main () {
    /*struct treenode t2 = {2, NULL,NULL};
    struct treenode t11 = {11, NULL,NULL};
    struct treenode t6 = {6, NULL,NULL};
    struct treenode t10 = {10, NULL,NULL};
    struct treenode t12 = {12,NULL,NULL};
    struct treenode t8 = {8,NULL, &t11};
    struct treenode t4 = {4, &t2, NULL};
    struct treenode t1 = {1, &t10, NULL};
    struct treenode t9 = {9, &t4, &t6};
    struct treenode t7 = {7, &t12, &t1};
    struct treenode t3 = {3, &t8, &t9};
    struct treenode t5 = {5, &t3, &t7};
    Treeptr root = &t5;*/
    Treeptr root = NULL;
    int n;
    while((scanf("%d", &n)) == 1) {
        root = addtree(root,n);
    }

    printf("Tree is %s empty\n", empty(root)?"":"not");

    printf("Depth: %d\n", depth(root));

    inorder(root);
    printf("\n =========\n");
    myfun(root);
    printf("\n*************\n");
    //preorder(root);

    //root = deleteNode(root, 5);
    //inorder(root);
    printf("\n");
    
    printf("1 exists: %d\n", exists(root, 1));
    deleteTree(root);

return 0;
}