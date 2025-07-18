/*****************************
 * include libraries
 *****************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************
 * define datatypes
 *****************************/
typedef struct tag_node
{
    int vertex;
    struct tag_node *next;
} st_node;

int dfs_visited[1001] = {0,};
int dfs_ans[1001] = {0,};
int dfs_ans_cnt = 0;

/*****************************
 * function prototypes
 *****************************/
void add_edge(st_node **graph, int from, int to);
st_node *create_node(int vertex);
int bfs(st_node **graph, int size, int v_start, int **ans);
void dfs(st_node **graph, int v_start);
void destroy_graph(st_node **graph, int size);

/*****************************
 * main function
 *****************************/
int main(void)
{
    int n, m ,v;
    scanf("%d %d %d", &n, &m, &v);

    st_node **graph = (st_node **)malloc(sizeof(st_node*) * (n + 1));
    for (int i = 0; i < n + 1; i++)
    {
        graph[i] = NULL;
    }

    int v1, v2;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &v1, &v2);
        add_edge(graph, v1, v2);
        add_edge(graph, v2, v1);
    }
    
    int *bfs_ans = (int *)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n + 1; i++)
    {
        bfs_ans[i] = 0;
    }

    int bfs_ans_cnt = bfs(graph, n + 1, v, &bfs_ans);
    dfs(graph, v);


    for (int i = 0; i < dfs_ans_cnt; i++)
    {
        printf("%d ", dfs_ans[i]);
    }
    printf("\n");
    for (int i = 0; i < bfs_ans_cnt; i++)
    {
        printf("%d ", bfs_ans[i]);
    }


    destroy_graph(graph, n + 1);
    free(bfs_ans);

    return 0;
}

/*****************************
 * define functions
 *****************************/
void add_edge(st_node **graph, int from, int to)
{
    st_node *new_node = create_node(to);
    if (graph[from] == NULL)
    {
        graph[from] = new_node;
    }
    else
    {
        st_node *current = graph[from];

        if (current->vertex > to)
        {
            st_node *temp = graph[from];
            graph[from] = new_node;
            new_node->next = temp;
        }
        else
        {
            while (current->next != NULL && current->next->vertex < to)            
            {
                current = current->next;
            }

            st_node *temp = current->next;
            current->next = new_node;
            new_node->next = temp;
        }
    }
}

st_node *create_node(int vertex)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    new_node->vertex = vertex;
    new_node->next = NULL;

    return new_node;
}

int bfs(st_node **graph, int size, int v_start, int **ans)
{
    int *queue = (int *)malloc(sizeof(int) * size);
    int front = 0;
    int rear = 0;

    int *visited = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
    {
        queue[i] = 0;
        visited[i] = 0;
    }

    int ans_cnt = 0;

    queue[rear++] = v_start;
    visited[v_start] = 1;

    while (front < rear)
    {
        int pop = queue[front++];
        (*ans)[ans_cnt++] = pop;
    
        st_node *current = graph[pop];
        while (current != NULL)
        {
            if (visited[current->vertex] != 1)
            {
                queue[rear++] = current->vertex;
                visited[current->vertex] = 1;
            }

            current = current->next;
        }
    }

    free(queue);
    free(visited);

    return ans_cnt;
}

void dfs(st_node **graph, int v_start)
{
    dfs_ans[dfs_ans_cnt++] = v_start;
    dfs_visited[v_start] = 1;

    st_node *current = graph[v_start];

    while (current != NULL)
    {
        if (dfs_visited[current->vertex] != 1)
        {
            dfs_visited[current->vertex] = 1;
            dfs(graph, current->vertex);
        }
        current = current->next;
    }
}

void destroy_graph(st_node **graph, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (graph[i] != NULL)
        {
            st_node *current = graph[i];
            while(current != NULL)
            {
                st_node *temp = current;
                current = current->next;
                free(temp);
            }          
        }
    }
    free(graph);
}