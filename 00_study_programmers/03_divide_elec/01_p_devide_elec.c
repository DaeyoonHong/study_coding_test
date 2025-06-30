#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
    struct tage_edege *next;
    vertex *from;
    vertex *target;
} edge;
typedef struct tag_graph
{
    vertex *vertices;
    int vertex_count;
} graph;

graph *create_graph(void)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->vertices = NULL;
    g->vertex_count = 0;

    return g;
}
vertex *create_vertex(graph *g, v_element_type data)
{
    vertex *v = (vertex *)malloc(sizeof(vertex));
    v->data = data;
    v->visited = 0;
    v->index =-1;
    v->next = NULL;
    v->adjacency_list = NULL;

    return v;
}
void add_vertex(graph *g, vertex *v)
{
    if(g->vertices == NULL)
    {
        g->vertices = v;
    }
    else
    {
        vertex *current = g->vertices;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = v;
    }
    v->index = g->vertex_count++;
}
edge *create_edge(vertex *from, vertex *to)
{
    edge *e = (edge *)malloc(sizeof(edge));
    
    e->next = NULL;
    e->from = from;
    e->target = to;

    return e;
}
void add_edge(vertex *v, edge *e)
{
    e->next = v->adjacency_list;
    v->adjacency_list = e;
}
void delete_edge(edge *e)
{
    
}