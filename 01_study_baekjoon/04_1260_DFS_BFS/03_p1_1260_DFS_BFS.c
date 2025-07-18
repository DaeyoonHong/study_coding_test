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
    struct tag_node *next;
    int vertex;
} st_node;

st_node *graph[1001];

typedef struct tag_bfs_queue
{
    st_node **queue;
    int front;
    int rear;
} st_bfs_queue;

int bfs_ans[1001] = {0,};
int bfs_ans_cnt = 0;
int bfs_visited[1001] = {0,};

int dfs_ans[1001] = {0,};
int dfs_visited[1001] = {0,};
int dfs_ans_cnt = 0;

int n;
int m;
int v;
/*****************************
 * function prototypes
 *****************************/
void add_edge(int from, int to);
st_node *create_node(int vertex);
void bfs(int start_vertex);
/*****************************
 * main function
 *****************************/
int main(void)
{
    scanf("%d %d %d", &n, &m, &v);

    int vertex1;
    int vertex2;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &vertex1, &vertex2);
        add_edge(vertex1, vertex2);
        add_edge(vertex2, vertex1);
    }

    bfs(v);

    for (int i = 0; i < bfs_ans_cnt; i++)
    {
        printf("%d ", bfs_ans[i]);
    }

    return 0;
}

/*****************************
 * define functions
 *****************************/
void add_edge(int from, int to)
{
    st_node *to_node = create_node(to);

    if (graph[from] == NULL)
    {
        graph[from] = to_node;
    }
    else
    {
        st_node *current = graph[from];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = to_node;
    }
}

st_node *create_node(int vertex)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    new_node->vertex = vertex;
    new_node->next = NULL;

    return new_node;
}

void bfs(int start_vertex)
{
    st_bfs_queue *bfs_queue = (st_bfs_queue *)malloc(sizeof(st_bfs_queue));
    bfs_queue->queue = (st_node **)malloc(sizeof(st_node *) * 1001);
    bfs_queue->front = 1;
    bfs_queue->rear = 1;

    for (int i = 0; i < 1001; i++)
    {
        bfs_queue->queue[i] = NULL;
    }

    bfs_queue->queue[bfs_queue->rear++] = graph[start_vertex];
    bfs_visited[start_vertex] = 1;
    bfs_ans[bfs_ans_cnt++] = start_vertex;
    bfs_visited[graph[start_vertex]->vertex] = 1;

    while (bfs_queue->front < bfs_queue->rear)
    {
        st_node *pop = bfs_queue->queue[bfs_queue->front++];
        bfs_ans[bfs_ans_cnt++] = pop->vertex;

        st_node *current = pop;
        while (current != NULL)
        {
            if (bfs_visited[current->vertex] != 1)
            {
                bfs_queue->queue[bfs_queue->rear++] = current;
                bfs_visited[current->vertex] = 1;
            }
            current = current->next;
        }
    }

    free(bfs_queue->queue);
    free(bfs_queue);
}