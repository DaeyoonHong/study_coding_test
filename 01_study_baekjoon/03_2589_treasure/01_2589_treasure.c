/************************
 * include libraries
 ************************/
#include <stdio.h>
#include <stdlib.h>

/************************
 * define datatypes
 ************************/
#define MAX 2500
#define MAX_H 50
#define MAX_L 50

int H, W;
char map[MAX_H][MAX_L];

 /* 연결 리스트 노드 구조체 */
typedef struct tag_g_node
{
   int index;
   struct tag_g_node * next;
} vertex;

/* 그래프 */
vertex * adj[MAX];

/* 링크드 큐 */
typedef struct tag_lq_node
{
    vertex * vertex;
    int depth;
    struct tag_lq_node * next;
} lq_node;

typedef struct tag_linked_queue
{
    lq_node * front;
    lq_node * rear;
    int count;
} linked_queue;

/***********************
 * function prototypes
 ***********************/
void add_edge(int from, int to);
void build_graph(void);
void free_graph(void);

/**********************
 * maing function
 **********************/
int main(void)
{
    /* 데이터를 입력 받고 그래프 생성 */
    scanf("%d %d", &H, &W);
    for(int i = 0 ; i < (H) ; i++)
    {
        for(int j = 0 ; j < W ; j++)
        {
            scanf("%1c", &map[i][j]);
        }
    }
    build_graph();

    /* 큐를 이용한 너비 우선 탐색 구현*/
    

    return 0;
}

/*********************
 * define functions
 *********************/
void build_graph()
{
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for(int i = 0 ; i < MAX_H ; i++)
    {
        for(int j = 0 ; j < MAX_L ; j++)
        {
            if(map[i][j] != 'L') continue;   
            int from = (i * W) + j;

            for(int k = 0 ; k < 4 ; k++)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];

                if(map[nx][ny] != 'L') continue;
                if(nx < 0 || ny <0 || nx >= W || ny >= H) continue;
                
                int to = (nx * W) + ny;
                
                add_edge(from, to);
            }
        }
    }
}

void add_edge(int from, int to)
{
    vertex * new_node = (vertex *)malloc(sizeof(vertex));
    new_node -> index = to;
    new_node -> next = adj[from]; /* from 의 인접리스트끼리 연결 */
    adj[from] = new_node;
}

void dfs(vertex ** adj, linked_queue * queue)
{
    for(int i = 0 ; i < (H * W) ; i++)
    {
        vertex * current = adj[i];
        int depth = 0;
        lq_enqueue(queue, lq_create_node(current), depth);
        while(!lq_is_empty(queue))
        {
            lq_node * popped = lq_dequeue(queue);
            current = popped -> vertex;

            while(current != NULL)
            {
                current = current -> next;
                if(current != NULL)
                {
                    lq_enqueue(queue, lq_creat_node(current), depth);
                }
            }
        }
    }
}

linked_queue * lq_create_queue()
{
    linked_queue * queue = (linked_queue *)malloc(sizeof(linked_queue));
    queue -> front = NULL;
    queue -> rear = NULL;
    queue -> count = 0;

    return queue;
}