#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 50
#define MAX_W 50
#define MAX_V (MAX_H * MAX_W)

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

char map[MAX_H][MAX_W + 1];
int H, W;
Node* adj[MAX_V];

void add_edge(int from, int to) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = to;
    newNode->next = adj[from];
    adj[from] = newNode;
 }

void build_graph() {
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (map[y][x] != 'L') continue;

            int v = y * W + x;

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d];
                int nx = x + dx[d];

                if (ny < 0 || ny >= H || nx < 0 || nx >= W) continue;
                /* 배열 인덱스에 범위를 벗어난 값이 입력되는 것을 방지 */
                if (map[ny][nx] != 'L') continue;

                int u = ny * W + nx;
                add_edge(v, u);
            }
        }
    }
}

int bfs(int start) {
    int visited[MAX_V] = {0};
    int dist[MAX_V] = {0};
    int queue[MAX_V];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    int max_dist = 0;

    while (front < rear) /* queue 가 비었을 때 */
    {
        int cur = queue[front++]; 

        /* for (Node* p = adj[cur]; p != NULL; p = p->next) */

        Node * p = adj[cur];
        /* p : cur 에 연결된 정점 */
        while(p != NULL)
        {
            int next = p->vertex;
            if (!visited[next]) 
            {
                visited[next] = 1;
                dist[next] = dist[cur] + 1;
                if (dist[next] > max_dist) max_dist = dist[next];
                queue[rear++] = next;
            }
            p = p -> next;
        }
    }

    return max_dist;
}

void free_graph() {
    for (int i = 0; i < H * W; i++) {
        Node* p = adj[i];
        while (p) {
            Node* tmp = p;
            p = p->next;
            free(tmp);
        }
    }
}

int main() {
    scanf("%d %d", &H, &W);
    for (int i = 0; i < H; i++) {
        scanf("%s", map[i]);
    }

    build_graph();

    int result = 0;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (map[y][x] == 'L') {
                int start = y * W + x;
                int d = bfs(start);
                if (d > result) result = d;
            }
        }
    }

    printf("%d\n", result);

    free_graph();
    return 0;
}