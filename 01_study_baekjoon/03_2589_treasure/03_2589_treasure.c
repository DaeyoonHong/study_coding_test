/************************
 * include libraries
 ************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************
 * define datatypes
 ************************/
#define MAX_H 50
#define MAX_W 50
#define MAX_V (MAX_H * MAX_W)

typedef struct node
{
    int vertex;
    struct node * next;
} node;
node * adj[MAX_V];

char map[MAX_H][MAX_W + 1];
int H, W;

/***********************
 * function prototypes
 ***********************/
void build_graph();
void add_edge(int from, int to);
int bfs(int start);
void free_graph();

/***********************
 * main function
 ***********************/
int main(void)
{
    scanf("%d %d", &H, &W);
    for(int i = 0 ; i < H ; i++)
    {
        scanf("%s", map[i]);
    }

    build_graph();

    int result = 0;
    for(int y = 0 ; y < H ; y++)
    {
        for(int x = 0 ; x < W ; x++)
        {
            if(map[y][x] == 'L')
            {
                int start = y * W + x;
                int d = bfs(start);
                if(d > result)
                {
                    result = d;
                }
            }
        }
    }
    printf("%d\n", result);

    free_graph();

    return 0;
}

/**********************
 * define functions
 **********************/
void build_graph()
{
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    for(int y = 0 ; y < H ; y++)
    {
        for(int x = 0 ; x < W ; x++)
        {
            if(map[y][x] != 'L') continue;

            int from = y * W + x; /* '높이 * 너비 + 너비' 의 형식으로 계산해야 올바른 인덱스 배정 가능 */
            for(int i = 0 ; i < 4 ; i++)
            {
                int ny = y + dy[i];
                int nx = x + dx[i];

                if(ny < 0 || nx < 0 || ny >= H || nx >= W) continue;
                if(map[ny][nx] != 'L') continue;

                int to = ny * W + nx;
                add_edge(from, to);
            }
        }
    }
}

void add_edge(int from, int to)
{
    node * new_node = (node *)malloc(sizeof(node));
    new_node -> vertex = to;
    new_node -> next = adj[from];
    adj[from] = new_node;
}

int bfs(int start)
{
    int visited[MAX_V] = {0,};
    int dist[MAX_V] = {0,};
    int queue[MAX_V];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    int max_dist = 0;

    while(front < rear)
    {
        int cur = queue[front++];

        node * p = adj[cur];
        while(p != NULL)
        {
            if(!visited[p -> vertex])
            {
                visited[p -> vertex] = 1;
                dist[p -> vertex] = dist[cur] + 1;
                queue[rear++] = p -> vertex;

                if(dist[p -> vertex] > max_dist)
                {
                    max_dist = dist[p -> vertex];
                }
            }                
            p = p -> next;
        }
    }
    return max_dist;
}

void free_graph()
{
    for(int i = 0; i < H * W ; i++)
    {
        node * p = adj[i];
        while(p)
        {
            node * temp = p;
            p = p -> next;
            free(temp);
        }
    }
}