#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/************************************
* define datatypes
*************************************/
typedef struct tag_node
{
    int vertex;
    struct tag_node *next;
} st_node;

int visited[101] = {0,};
int dfs_cnt = 0;
/************************************
* function prototypes
*************************************/
void add_edge(st_node **graph, int from, int to);
void delete_edge(st_node **graph, int delete_from, int delete_to);
void dfs(st_node **graph, int start_v);


/************************************
* solution
*************************************/
// wires_rows는 2차원 배열 wires의 행 길이, wires_cols는 2차원 배열 wires의 열 길이입니다.
int solution(int n, int** wires, size_t wires_rows, size_t wires_cols) 
{
    int answer = -1;
    
    st_node **graph = (st_node **)malloc(sizeof(st_node *) * (n + 1));
    for(int i = 0; i < n + 1; i++)
    {
        graph[i] = NULL;
    }
    
    for (int i = 0; i < wires_rows; i++)
    {
        int v1 = wires[i][0];
        int v2 = wires[i][1];
        
        add_edge(graph, v1, v2);
        add_edge(graph, v2, v1);
    }

    
    for (int i = 0; i < wires_rows; i++)
    {
        dfs_cnt = 0;
        int delete_from = wires[i][0];
        int delete_to = wires[i][1];
        
        delete_edge(graph, delete_from, delete_to);
        
        dfs(graph, delete_from);
        for(int i = 0; i < 101; i++)
        {
            visited[i] = 0;
        }
        
        int diff = n - 2 * dfs_cnt;
        if(diff < 0)
        {
            diff = diff * -1;
        }
        
        if(answer > diff || answer == -1)
        {
            answer = diff; 
        }
        
        add_edge(graph, delete_from, delete_to);
    }
    
    return answer;
}


/*************************************
* define functions
**************************************/
void add_edge(st_node **graph, int from, int to)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    new_node->vertex = to;
    new_node->next = NULL;

    if(graph[from] == NULL)
    {
        graph[from] = new_node;
        return;
    }
    
    st_node *temp = graph[from];
    graph[from] = new_node;
    new_node->next = temp;
}

void delete_edge(st_node **graph, int delete_from, int delete_to)
{
    st_node *current = graph[delete_from];
    
    if (current->vertex == delete_to)
    {
        graph[delete_from] = current->next;
        free(current);
        return;
    }
    
    while (current->next->vertex != delete_to)
    {
        current = current->next;
    }
    st_node *delete = current->next;
    current->next = current->next->next;
    free(delete);
}

void dfs(st_node **graph, int start_v)
{
    visited[start_v] = 1;
    dfs_cnt++;
    st_node *current = graph[start_v];
    
    while (current != NULL)
    {
        if(visited[current->vertex] != 1)
        {
            dfs(graph, current->vertex);
        }
        current = current->next;
    }
}



