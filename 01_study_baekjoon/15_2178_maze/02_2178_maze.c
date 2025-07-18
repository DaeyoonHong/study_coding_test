/*****************************
 * include libraries
 *****************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************
 * define datatypes
 *****************************/
int m, n;
typedef struct tag_node
{
    int idx;
    struct tag_node *next;
} st_node;

/*****************************
 * function prototypes
 *****************************/
int get_graph_idx(int x, int y);
void create_edge(st_node **graph, int **map, int y, int x);
st_node *create_node(int y, int x);
void add_node(st_node **graph, int idx, st_node *new_node);
int bfs(st_node **graph, int start_idx, int target_idx);

/*****************************
 * main function
 *****************************/
int main(void)
{
    scanf("%d %d", &n, &m);

    /* 그래프 배열 생성 및 초기화 */
    st_node **graph = (st_node **)malloc(sizeof(st_node *) * n * m);
    for (int i = 0; i < n * m; i++)
    {
        graph[i] = NULL;
    }
    
    /* 이차원 배열 동적 할당 */
    int **map = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        map[i] = (int *)malloc(sizeof(int) * m);
    }

    /* map 생성 */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%1d", &map[i][j]);
        }
    }

    /* graph 생성 */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == 1)
            {
                create_edge(graph, map, i, j);
            }
        }
    }

    printf("%d", bfs(graph, get_graph_idx(0, 0), get_graph_idx(m - 1, n - 1)));

    free(graph);
    for (int i = 0; i < n; i++)
    {
        free(map[i]);
    }
    free(map);

    return 0;
}

/*****************************
 * define functions
 *****************************/
int get_graph_idx(int x, int y)
{
    return m * y + x;
}

void create_edge(st_node **graph, int **map, int y, int x)
{
    int idx = get_graph_idx(x, y);

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++)
    {
        int new_y = y + dy[i];
        int new_x = x + dx[i];

        if (new_y >= 0 && new_y < n && new_x >= 0 && new_x < m && map[new_y][new_x] == 1)
        {
            st_node *new_node = create_node(new_y, new_x);
            add_node(graph, idx, new_node);
        }

    }
}

st_node *create_node(int y, int x)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    new_node->idx = get_graph_idx(x, y);
    new_node->next = NULL;

    return new_node;
}

void add_node(st_node **graph, int idx, st_node *new_node)
{
    st_node *current = graph[idx];

    if (current == NULL)
    {
        graph[idx] = new_node;
    }
    else
    {
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

int bfs(st_node **graph, int start_idx, int target_idx)
{
    printf("%d", target_idx);
    int *visited = (int *)calloc(n * m, sizeof(int));
    int *dist = (int *)calloc(n * m, sizeof(int));
    st_node **queue = (st_node **)malloc(sizeof(st_node *) * n * m);
    int front = 0;
    int rear = 0;

    queue[rear++] = graph[start_idx];
    visited[start_idx] = 1;
    dist[start_idx] = 1;

    while (front < rear)
    {

        st_node *pop = queue[front++];
        int cur_idx = pop->idx;
        printf("%d\n", cur_idx);
        if (cur_idx == target_idx)
        {
            printf("here");
            int result = dist[cur_idx];
            free(queue);
            free(visited);
            free(dist);
            return result;
        }
        st_node *current = graph[cur_idx];
        while (current != NULL)
        {
            int next_idx = current->idx;
            if (!visited[next_idx])
            {
                queue[rear++] = graph[next_idx];
                visited[next_idx] = 1;
                dist[next_idx] = dist[cur_idx] + 1;
            }
            current = current->next;
        }
    }
    free(queue);
    free(visited);
    free(dist);
    return 0;
}
