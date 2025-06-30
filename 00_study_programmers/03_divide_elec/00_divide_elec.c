/*************************
 * include libraries
 *************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**************************
 * define datatypes
 **************************/
typedef int v_element_type;
typedef struct tag_vertex
{
    v_element_type data;
    int visited;
    int index;

    struct tag_vertex *next;
    struct tag_edge *adjacency_list;
} vertex;
typedef struct tag_edge
{
    struct tag_edge *next;
    vertex *from;
    vertex *target;
} edge;
typedef struct tag_graph
{
    vertex *vertices;
    int vertex_count;
} graph;

/*************************
 * function prototypes
 *************************/

/**************************
 * main function
 **************************/

// wires_rows는 2차원 배열 wires의 행 길이, wires_cols는 2차원 배열 wires의 열 길이입니다.
int solution(int n, int **wires, size_t wires_rows, size_t wires_cols)
{
    int answer = -1;

    /* 정점 생성 */

    graph *g = create_graph();
    for (int i = 1; i < n + 1; i++)
    {
        vertex *v = create_vertex(i);
        add_vertex(g, v);
    }

    edge **e = (edge **)malloc(sizeof(edge *) * wires_rows);
    /* 간선 연결  */
    for (int i = 0; i < wires_rows; i++)
    {
        int from_idx = wires[i][0];
        int target_idx = wires[i][1];
        vertex *from = get_vertex(g, from_idx);
        vertex *target = get_vertex(g, target_idx);

        e[i] = creat_edge(from, target);

        add_edge(from, e[i]);
    }

    /* 간선 하나 없애고 순회 */
    /* 간선 총 개수 : wires_rows */
    /* i 번째 간선을 제거하는 반복문 */
    int abs;
    int max_abs = 0;
    for (int i = 0; i < wires_rows; i++)
    {
        delete_edge(e[i]);
        int cnt = dfs();
        int a = n - cnt;
        int b = n - a;
        if (a > b)
        {
            abs = a;
        }
        else
        {
            abs = b;
        }
        if(max_abs < abs)
        {
            max_abs = abs;
        }
        add_edge(e[i]->from, e[i]);
    }

    answer = max_abs;
    
    return answer;
}

/******************************
 * define functions
 ******************************/
vertex *create_vertex(v_element_type data)
{
    vertex *v = (vertex *)malloc(sizeof(vertex));
    v->data = data;
    v->next = NULL;
    v->adjacency_list = NULL;
    v->visited = 0;
    v->index = -1;

    return v;
}

graph *create_graph(void)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->vertices = NULL;
    g->vertex_count = 0;

    return g;
}

void add_vertex(graph *g, vertex *v)
{
    vertex *vertex_list = g->vertices;
    if (vertex_list == NULL)
    {
        g->vertices = v;
    }
    else
    {
        while (vertex_list->next != NULL)
        {
            vertex_list = vertex_list->next;
        }
        vertex_list->next = v;
    }
    v->index = g->vertex_count++;
}

edge *create_edge(vertex *from, vertex *target)
{
    edge *e = (edge *)malloc(sizeof(edge));
    e->from = from;
    e->target = target;
    e->next = NULL;

    return e;
}

vertex *get_vertex(graph *g, int idx)
{
    vertex *current_vertex = g->vertices;
    for (int i = 1; i < idx; i++)
    {
        current_vertex = current_vertex->next;
    }
    return current_vertex;
}

void add_edge(vertex *v, edge *e)
{
    if (v->adjacency_list == NULL)
    {
        v->adjacency_list = e;
    }
    else
    {
        edge *adjacency_list = v->adjacency_list;
        while (adjacency_list->next != NULL)
        {
            adjacency_list = adjacency_list->next;
        }
        adjacency_list->next = e;
    }
}

void delete_edge(edge *e)
{
    vertex *from = e->from;
    edge *adjacency_list = from->adjacency_list;

    if (adjacency_list == e)
    {
        from->adjacency_list = e->next;
    }
    else
    {
        while (adjacency_list->next != e)
        {
            adjacency_list = adjacency_list->next;
        }
        adjacency_list->next = e->next;
    }
}

int dfs()
{
}