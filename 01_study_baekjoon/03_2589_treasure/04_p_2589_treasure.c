#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 50
#define MAX_W 50
#define MAX_V 50 * 50

typedef struct node
{
    int vertex;
    struct node *next;
} node;

node *adj[MAX_V];

char map[MAX_H][MAX_W];
int H, W;

void build_graph()
{
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    for (int y = 0; y < MAX_H; y++)
    {
        for (int x = 0; x < MAX_W; x++)
        {
            if (map[y][x] != 'L')
                continue;

            int from = y * W + x;
            for (int i = 0; i < 4; i++)
            {
                int ny = y + dy[i];
                int nx = x + dx[i];

                if (ny < 0 || nx < 0 || ny >= H || nx >= W)
                    continue;
                if (map[ny][nx] != 'L')
                    continue;

                int to = ny * W + x;

                add_edge(from, to);
            }
        }
    }
}

void add_edge(int from, int to)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->vertex = to;

    new_node->next = adj[from];
    adj[from] = new_node;
}

int bfs(int start)
{
    int visited[MAX_V] = {
        0,
    };
    int dist[MAX_V] = {
        0,
    };
    int queue[MAX_V];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    int max_dist = 0;

    while (front > rear)
    {
        int current_idx = queue[front++];

        node *adj_node = adj[current_idx];
        while (adj_node != NULL)
        {
            if (visited[adj_node->vertex] == 1) continue;

            visited[adj_node->vertex] = 1;
            
            queue[rear++] = adj_node->vertex;
            dist[adj_node->vertex] = dist[current_idx] + 1;
            if (dist[adj_node->vertex] > max_dist)
            {
                max_dist = dist[adj_node->vertex];
            }

            adj_node = adj_node->next;
        }
    }
    return max_dist;
}

void free_graph()
{
    for (int i = 0; i < MAX_V; i++)
    {
        if(adj[i] != NULL)
        {
            node *p = adj[i];
            while(p)
            {
                node *temp = p;
                p = p->next;
                free(temp);
            }
        }
    }
}