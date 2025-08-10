#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_H 50
#define MAX_W 50

typedef struct tag_node
{
    int vertex; /* x * MAX_H + y */
    struct tag_node *next;
} st_node;

st_node **graph[MAX_H * MAX_W];

int map[MAX_H][MAX_W] = {0,};
int visited_map[MAX_H][MAX_W] = {0,};

int temp_ans = 0;
int temp_ans1 = 0;
int temp_ans2 = 0;

void build_map(int **rectangle, size_t rectangle_row_len);
void build_graph(int characterX, int characterY);
void dfs(st_node **graph, int vertex, int target);

// rectangle_row_len은 2차원 배열 rectangle의 행(세로) 길이입니다.
// rectangle_col_len은 2차원 배열 rectangle의 열(가로) 길이입니다.
// rectangle[i][j]는 rectangle의 i번째 행의 j번째 열에 저장된 값을 의미합니다.
int solution(int **rectangle, size_t rectangle_row_len, size_t rectangle_col_len, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    
    build_map(rectangle, rectangle_row_len);
    
    build_graph(characterX, characterY);
    
    dfs(graph, characterX * MAX_H + characterY, itemX * MAX_H + itemY);
    temp_ans1 = temp_ans;
    temp_ans = 0;
    
    dfs(graph, itemX * MAX_H + itemY, characterX * MAX_H + characterY);
    temp_ans2 = temp_ans;
    
    if(temp_ans1 >= temp_ans2)
    {
        answer = temp_ans1;
    }
    else
    {
        answer = temp_ans2;
    }    
    
    return answer;
}

void build_map(int **rectangle, size_t rectangle_row_len)
{
     for (int i = 0; i < rectangle_row_len; i++)
    {
        int x_left = rectangle[i][0];
        int y_left = rectangle[i][1];
        int x_right = rectangle[i][2];
        int y_right = rectangle[i][3];
        
        int x = x_left;
        int y = y_left;
        
        while (x <= x_right)
        {
            map[x][y_left] = 1;
            map[x][y_right] = 1;
            
            x++;
        }
        
        while (y <= y_right)
        {
            map[x_left][y] = 1;
            map[x_right][y] = 1;
            
            y++;
        } 
    } 
}

void build_graph(int characterX, int characterY)
{
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    
    int x_current = characterX;
    int y_current = characterY;
    
    for (int i = 0; i < 4; i++)
    {
        int x_next = x_current + dx[i];
        int y_next = y_current + dy[i];
        
        int i_0 = 0, i_1 = 0, i_2 = 0, i_3 = 0;

        if (map[x_next][y_next] == 1 && visited_map[x_next][y_next] == 0)
        {
            visited_map[x_next][y_next] = 1;
            
            if (i == 0) { i_0 = 1; }      
            else if (i == 1) { i_1 = 1; }
            else if (i == 2) { i_2 = 1; }
            else {i_3 = 1;}
        }
        
        if (i_0 == 1 && i_1 == 1 && i_2 == 1 && i_3 ==0) 
        { 
            x_next = x_current + dx[0];
            y_next = y_current + dy[0];
        }
        else if (i_0 == 1 && i_1 == 1 && i_2 == 0 && i_3 ==1)
        {
            x_next = x_current + dx[1];
            y_next = y_current + dy[1];            
        }
        else if (i_0 == 1 && i_1 == 0 && i_2 == 1 && i_3 ==1)
        {
            x_next = x_current + dx[2];
            y_next = y_current + dy[2];            
        }
        else if (i_0 == 0 && i_1 == 1 && i_2 == 1 && i_3 ==1)
        {
            x_next = x_current + dx[3];
            y_next = y_current + dy[3];            
        }
    }
}   

void dfs(st_node **graph, int vertex, int target)
{   
    temp_ans++;
    st_node *next = graph[vertex]->next;
    
    if (next->vertex == target)
    {
        return;
    }
    else
    {
        dfs(graph, next->vertex, target);
    }
}
