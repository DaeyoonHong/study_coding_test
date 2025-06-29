#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int vertex;
    struct node *next;
} node;

int n = 0;
int m = 0;
int dfs_visited[1001] = {0};

node *create_node(int v);
void add_edge(node **adj, int from, int to);  // 매개변수 타입 변경
void bfs(node **adj, int start_v);
void dfs(node **adj, int start_v);
void destroy_adj(node **adj);

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
        add_edge(adj, v1, v2);  // 구조체 노드 대신 정수형 전달
        add_edge(adj, v2, v1);
    }

    dfs(adj, start_v);
    printf("\n");
    bfs(adj, start_v);

    destroy_adj(adj);
    return 0;
}

node *create_node(int v)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}

void add_edge(node **adj, int from, int to)
{
    node *new_node = create_node(to);
    node **head = &adj[from];

    if (*head == NULL || (*head)->vertex > to)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    node *current_node = *head;
    while (current_node->next != NULL && current_node->next->vertex < to)
    {
        current_node = current_node->next;
    }

    new_node->next = current_node->next;
    current_node->next = new_node;
}

void bfs(node **adj, int start_v)
{
    int *queue = (int *)malloc(sizeof(int) * (n + 1));  // n -> n + 1
    int front = 0, rear = 0;
    int *visited = (int *)malloc(sizeof(int) * (n + 1));

    for (int i = 0; i <= n; i++)  // <= n 로 수정
    {
        queue[i] = 0;
        visited[i] = 0;
    }

    queue[rear++] = start_v;
    visited[start_v] = 1;

    while (front < rear)
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
        if (dfs_visited[current_node->vertex] == 0)
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
        node *current_node = adj[i];
        while (current_node != NULL)
        {
            node *temp = current_node;
            current_node = current_node->next;
            free(temp);
        }
    }
    free(adj);
}