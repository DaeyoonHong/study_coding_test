/*****************************
 * include libraries
 *****************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************
 * define datatypes
 *****************************/
#define MAX_H 100
#define MAX_W 100
#define R_G_B 0
#define RG_B 1

int visited[MAX_H * MAX_W] = {0,};
int visited_rg[MAX_H * MAX_W] = {0,};
char map[MAX_H][MAX_W + 1];

int dfs_cnt;

typedef struct tag_node
{
    int vertex;
    struct tag_node *next;
} st_node;

/*****************************
 * function prototypes
 *****************************/
void build_graph(st_node **graph, int size_of_map, int rgb);
void add_node(st_node **graph, int from, int to);
void dfs(st_node **graph, int *visited, int vertex);

/*****************************
 * main function
 *****************************/
int main(void)
{
    int size_of_map;
    int size_of_graph;
    int ans = 0;
    int ans_rg = 0;
    
    scanf("%d", &size_of_map);
    
    size_of_graph = size_of_map * size_of_map;
    
    for (int i = 0; i < size_of_map; i++)
    {
        scanf("%100s", map[i]);
    }

    st_node **graph = (st_node **)malloc(sizeof(st_node *) * size_of_graph);
    st_node **graph_rg = (st_node **)malloc(sizeof(st_node *) * size_of_graph);
    
    for (int i = 0; i < size_of_graph; i++)
    {
        graph[i] = NULL;
        graph_rg[i] = NULL;
    }
    
    build_graph(graph, size_of_map, R_G_B);
    build_graph(graph_rg, size_of_map, RG_B);
    
for (int i = 0; i < size_of_graph; i++)
{
    if (visited[i] == 0)
    {
        dfs(graph, visited, i);
        ans++;
    }
}

for (int i = 0; i < size_of_graph; i++)
{
    if (visited_rg[i] == 0)
    {
        dfs(graph_rg, visited_rg, i);
        ans_rg++;
    }
}

printf("%d %d\n", ans, ans_rg);
    
    
    return 0;
}

/*****************************
 * define functions
 *****************************/
void build_graph(st_node **graph, int size_of_map, int rgb)
{
    int dh[4] = {1, -1, 0, 0};
    int dw[4] = {0, 0, 1, -1};
    
    for (int i = 0; i < size_of_map; i++)
    {
        for (int j = 0; j < size_of_map; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if(i + dh[k] >= 0 && i + dh[k] < size_of_map && 
                   j + dw[k] >= 0 && j + dw[k] < size_of_map)
                {
                    if (map[i][j] == map[i + dh[k]][j + dw[k]])
                    {
                        int from = i * size_of_map + j;
                        int to = (i + dh[k]) * size_of_map +(j + dw[k]);
                        
                        add_node(graph, from, to);
                    }
                    else if (rgb == RG_B &&
                            (map[i][j] == 'R' || map[i][j] == 'G') &&
                            (map[i + dh[k]][j + dw[k]] == 'R' || map[i + dh[k]][j + dw[k]] == 'G'))
                    {
                        int from = i * size_of_map + j;
                        int to = (i + dh[k]) * size_of_map +(j + dw[k]);
                        
                        add_node(graph, from, to);
                    }
                }
            }
        }
    }
}

void add_node(st_node **graph, int from, int to)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    new_node->vertex = to;
    
    st_node *temp = graph[from];
    graph[from] = new_node;
    new_node->next = temp;
    //printf("from: %d, added vertex : %d\n", from, graph[from]->vertex);
}

void dfs(st_node **graph, int *visited, int vertex)
{
    visited[vertex] = 1;

    st_node *current = graph[vertex];
    while (current != NULL)
    {
        if (visited[current->vertex] == 0)
        {
            dfs(graph, visited, current->vertex);
        }
        current = current->next;
    }
}