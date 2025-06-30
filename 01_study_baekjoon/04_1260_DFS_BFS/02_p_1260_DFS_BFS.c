#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int vertex;
    struct node *next;
} node;

int n = 0;
int m = 0;
int visited[1001] = {0, };

node *create_node(int v)
{
    node *new_node = (node *)malloc(sizeof(node *));
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}
void add_edge(node **adj, int from, int to)
{
    node *new_node = create_node(to);
    node **head = &adj[from]; /* 포인터 복사 안전하게 하기 위해 */

    if (*head == NULL || (*head)->vertex > to)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    node *current_node = *head;
    while(current_node->next != NULL && current_node->next->vertex < to)
    {
        current_node = current_node->next;
    }
    new_node->next = current_node->next;
    current_node->next = new_node;
}
void bfs(node **adj, int start_vertex)
{
    int *queue = (int *)malloc(sizeof(int) * (n + 1));
    int front = 0, rear = 0;

    for (int i = 0; i < n + 1; i++)
    {
        queue[i] = 0;
        visited[i] = 0;
    }

    /* bfs 출발점 입력 */
    queue[rear++] = start_vertex;
    while(front > rear)
    {
        int current = queue[front++];
        node *p = adj[current];
        while(p != NULL)
        {
            if(visited[p->vertex] != 1)
            {
                visited[p->vertex] = 1;
                queue[rear++] = p->vertex;
            }
            p = p->next;
        }
    }
    for(int i = 0; i < rear; i++)
    {
        printf("%d ", queue[i]);
    }
    for (int i = 0; i < n + 1; i++)
    {
        visited[i] = 0;
    }

    free(queue);
    free(visited);
}
void dfs(node **adj, int start_vertex)
{
    printf("%d ", start_vertex);
    for (int i = 0; i < n + 1; i++)
    {
        visited[i] = 0;
    }
    visited[start_vertex] = 1;
    node *current_node = adj[start_vertex];

    while(current_node != NULL)
    {
        if(visited[current_node->vertex] == 0)
        {
            dfs(adj, current_node->vertex);
        }
        current_node = current_node->next;
    }
    
}
void destroy_adj(node **adj)
{
    for(int i =0; i < n + 1; i++)
    {
        node *current_node = adj[i];
        while(current_node != NULL)
        {
            node *temp = current_node;
            current_node = current_node->next;
            free(temp);
        }
    }
    free(adj);
}
int main(void)
{
    int start_vertex = 0;

    scanf("%d %d %d", &n, &m, &start_vertex);

    node **adj = (node **)malloc(sizeof(node *) * (n + 1)); /* n = 5 인 경우 5번 노드까지 존재*/
    for(int i = 0; i <= n; i++)
    {
        adj[i] = NULL;
    }

    for(int i = 0; i < m; i++)
    {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        add_edge(adj, v1, v2);
        add_edge(adj, v2, v1);
    }

    dfs(adj, start_vertex);
    printf("\n");
    bfs(adj, start_vertex);

    destroy_adj(adj);
    return 0;  
}
