/***********************************
 * include libraries
 ***********************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************
 * include datatypes
 ***********************************/
typedef struct tag_node
{
    int data;
    struct tag_node *left;
    struct tag_node *right;
} st_node;

st_node *binary_tree;

int c;
/***********************************
 * function prototypes
 ***********************************/
 void insert(int x, st_node *head);
 st_node *create_node(int data);
 void destroy_binary_tree(st_node *head);

/**********************************
 * main function
 **********************************/
int main(void)
{
    int n;
    int x;

    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        if(i == 0)
        {
            st_node *root = create_node(x);
            binary_tree = root;
            printf("0\n");
        }
        else
        {
            insert(x, binary_tree);
        }
    }

    destroy_binary_tree(binary_tree);
    return 0;
}

/*************************************
 * define functions
 *************************************/
st_node *create_node(int data)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void insert(int x, st_node *head)
{
    c++;
    if(x < head->data)
    {
        if(head->left == NULL)
        {
            st_node *new_node = create_node(x);
            head->left = new_node;
            printf("%d\n", c);
        }
        else
        {
            insert(x, head->left);
        }
    }
    else if(x > head->data)
    {
        if(head->right == NULL)
        {
            st_node *new_node = create_node(x);
            head->right = new_node;
            printf("%d\n", c);
        }
        else
        {
            insert(x, head->right);
        }
    }

}

void destroy_binary_tree(st_node * head)
{
    if(head->left != NULL)
    {
        destroy_binary_tree(head->left);
    }
    else if(head->right != NULL)
    {
        destroy_binary_tree(head->right);
    }
    else
    {
        free(head);
    }
}