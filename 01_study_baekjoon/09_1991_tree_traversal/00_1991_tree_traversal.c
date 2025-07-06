/******************************
 * include libraries
 ******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************
 * define datatypes
 ******************************/
typedef struct tag_node
{
    char left;
    char right;
    char data;
} st_node;

/********************************
 * function prototypes
 ********************************/
st_node *create_node(char data, char left, char right);
void destroy_node(st_node *node);
void destroy_tree(st_node **tree, int n);
void preorder_print_tree(st_node **tree, char data, int n);
void inorder_print_tree(st_node **tree, char data, int n);
void postorder_print_tree(st_node **tree, char data, int n);

/********************************
 * main function
 ********************************/
int main(void)
{
    int n;
    char parent, left, right;

    scanf("%d", &n);
    st_node **tree = (st_node **)malloc(sizeof(st_node *) * n);

    for(int i = 0; i < n; i++)
    {
        scanf(" %c %c %c", &parent, &left, &right);
        st_node *new_node = create_node(parent, left, right);
        tree[i] = new_node;
    }
    

    preorder_print_tree(tree, tree[0]->data, n);
    printf("\n");
    inorder_print_tree(tree, tree[0]->data, n);
    printf("\n");
    postorder_print_tree(tree, tree[0]->data, n);

    destroy_tree(tree, n);

    return 0;
}

/*********************************
 * define functions
 *********************************/
st_node *create_node(char data, char left, char right)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    new_node->left = left;
    new_node->right = right;
    new_node->data = data;

    return new_node;
}
void destroy_node(st_node *node)
{
    free(node);
}
void destroy_tree(st_node **tree, int n)
{
    for(int i = 0; i < n; i++)
    {
        destroy_node(tree[i]);
    }
}
void preorder_print_tree(st_node **tree, char data, int n)
{
    int index = 0;

    while(tree[index]->data != data)
    {
        index++;
    }

    printf("%c", tree[index]->data);
    
    if(tree[index]->left != '.')
    {
        preorder_print_tree(tree, tree[index]->left, n);
    }
    
    if(tree[index]->right != '.')
    {
        preorder_print_tree(tree, tree[index]->right, n);
    }
}
void inorder_print_tree(st_node **tree, char data, int n)
{
    int index = 0;

    while(tree[index]->data != data)
    {
        index++;
    }

    if(tree[index]->left != '.')
    {
        inorder_print_tree(tree, tree[index]->left, n);
    }

    printf("%c", tree[index]->data);

    if(tree[index]->right != '.')
    {
        inorder_print_tree(tree, tree[index]->right, n);
    }
}
void postorder_print_tree(st_node **tree, char data, int n)
{
    int index = 0;

    while(tree[index]->data != data)
    {
        index++;
    }

    if(tree[index]->left != '.')
    {
        postorder_print_tree(tree, tree[index]->left, n);
    }

    if(tree[index]->right != '.')
    {
        postorder_print_tree(tree, tree[index]->right, n);
    }
    
    printf("%c", tree[index]->data);
}
