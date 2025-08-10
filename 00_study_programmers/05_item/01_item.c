#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*****************************
* define data
******************************/
#define MAX 102

int map[MAX][MAX];

typedef struct tag_node
{
    int vertex;
    int dist;
    struct tag_node *next;
} st_node;

st_node **graph[MAX * MAX];

/****************************
* function prototypes
*****************************/
void build_map(int **rectangle, size_t rectangle_row_len);
void build_graph();
void add_node(int from, int to);
int bfs(int start_v, int target_v);

/****************************
* main function
*****************************/
int solution(int **rectangle, size_t rectangle_row_len, size_t rectangle_col_len, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    
    build_map(rectangle, rectangle_row_len);
    
    build_graph();

    int start_v = characterX * MAX + characterY;
    int target_v = itemX * MAX + itemY;
    
    answer = bfs(start_v, target_v);

    return answer;
}

/***************************
* define functions
****************************/
void build_map(int **rectangle, size_t rectangle_row_len)
{
    for (int i = 0; i < rectangle_row_len; i++)
    {
        int x_left = rectangle[i][0];
        int y_left = rectangle[i][1];
        int x_right = rectangle[i][2] * 2;
        int y_right = rectangle[i][3] * 2;
        
        for (int x = x_left; x <= x_right; x++)
        {
            for (int y = y_left; y <= y_right; y++)
            {
                if (x == x_left || y == y_left || x == x_right || y == y_right)
                {
                    map[x][y] = 1;
                }
                else
                {
                    map[x][y] = 2;
                }
            }
        }
    }   
}

void build_graph()
{
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    
    for (int x = 0; x < MAX; x++)
    {
        for(int y = 0; y < MAX; y++)
        {
            if (map[x][y] == 1)
            {
                for (int i = 0; i < 4; i++)
                {
                    int next_x = x + dx[i];
                    int next_y = y + dy[i];
                    
                    if (map[next_x][next_y] == 1)
                    {
                        int from = x * MAX + y;
                        int to = next_x * MAX + next_y;
                        
                        add_node(from, to);
                    }
                }
            }
        }
    } 
}

void add_node(int from, int to)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    new_node->vertex = to;
    new_node->dist = 0;
    
    st_node *temp = graph[from];
    graph[from] = new_node;
    new_node->next = temp;
}

int bfs(int start_v, int target_v)
{
    int *queue = (int *)malloc(sizeof(int) * MAX);
    int *visited = (int *)malloc(sizeof(int) * MAX);
    
    for (int i = 0; i < MAX; i++)
    {
        queue[i] = 0;
        visited[i] = 0;
    }
    
    int front = 0;
    int rear = 0;
    
    queue[rear++] = start_v;
    visited[start_v] = 1;
    
    while (front < rear)
    {
        int pop = queue[front++];
        
        st_node *current = graph[pop];
        
        int dist = current->dist;
        
        if (current->vertex == target_v)
        {
            return current->dist / 2;
        }
        
        
        while (current != NULL)
        {
            if (visited[current->vertex] == 0)
            {
                visited[current->vertex] = 1;
                queue[rear++] = current->vertex;
                current->dist = dist + 1;         
            }
            current = current->next;
        }
    }
    
    return 0;
}