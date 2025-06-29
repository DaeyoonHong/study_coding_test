/***********************
 * include libraries
 ***********************/
#include <stdio.h>
#include <stdlib.h>

/***********************
 * define data
 ***********************/
typedef struct node
{
    int vertex;
    struct node *next;
} node;

int n = 0;
int m = 0;

int dfs_visited[1001] = {
    0,
};
/***********************
 * functions prototypes
 ***********************/
node *create_node(int v);
void add_edge(node **adj, node *from, node *to);
void bfs(node **adj, int start_v);
void dfs(node **adj, int start_v);
void destroy_adj(node **adj);

/***********************
 * main function
 ***********************/
int main(void)
{
    int start_v = 0;

    scanf("%d %d %d", &n, &m, &start_v);

    node **adj = (node **)malloc(sizeof(node *) * (n + 1));
    for (int i = 0; i < n + 1; i++)
    {
        adj[i] = NULL;
    }
    for (int i = 0; i < m; i++)
    {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        node *node1 = create_node(v1);
        node *node2 = create_node(v2);

        add_edge(adj, node1, node2);
        add_edge(adj, node2, node1);
    }

    dfs(adj, start_v);
    printf("\n");
    bfs(adj, start_v);

    destroy_adj(adj);

    return 0;
}

/**********************
 * define functions
 **********************/
node *create_node(int v)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->vertex = v;
    new_node->next = NULL;

    return new_node;
}

void add_edge(node **adj, node *from, node *to)
{
    node **head = &adj[from->vertex];
    if (*head == NULL || (*head)->vertex > to->vertex)
    {
        to->next = *head;
        *head = to;
        return;
    }
    node *current_node = *head;
    while (current_node->next != NULL && current_node->next->vertex < to->vertex)
    {
        current_node = current_node->next;
    }

    to->next = current_node->next;
    current_node->next = to;
}

void bfs(node **adj, int start_v)
{
    int *queue = (int *)malloc(sizeof(int) * (n));
    int front = 0, rear = 0;

    int *visited = (int *)malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < n; i++)
    {
        queue[i] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        visited[i] = 0;
    }
    queue[rear++] = start_v;
    visited[start_v] = 1;
    while (front < rear) /* bfs : queue 가 빌때까지 반복 */
    {
        int current = queue[front++];
        node *p = adj[current];
        while (p != NULL)
        {
            if (visited[p->vertex] == 0)
            {
                queue[rear++] = p->vertex;
                visited[p->vertex] = 1;
            }
            p = p->next;
        }
    }

    for (int i = 0; i < rear; i++)
    {
        printf("%d ", queue[i]);
    }

    free(queue);
    free(visited);
}

void dfs(node **adj, int start_v)
{
    printf("%d ", start_v);
    dfs_visited[start_v] = 1;
    node *current_node = adj[start_v];

    while (current_node != NULL)
    {
        if (current_node != NULL && dfs_visited[current_node->vertex] == 0)
        {
            dfs(adj, current_node->vertex);
        }
        current_node = current_node->next;
    }
}

void destroy_adj(node **adj)
{
    for (int i = 0; i < n + 1; i++)
    {
        if (adj[i] != NULL)
        {
            node *current_node = adj[i];
            while (current_node != NULL)
            {
                node *temp = current_node;
                current_node = current_node->next;
                free(temp);
            }
        }
    }
    free(adj);
}
