#include <stdio.h>
#include <stdlib.h>

#define MAX 2500  // 50*50
#define MAX_H 50
#define MAX_W 50

int H, W;
char map[MAX_H][MAX_W + 1];  // 입력 지도

// 연결 리스트 노드 구조체
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 인접 리스트 배열
Node* adj[MAX];  // 각 정점에 대한 연결 리스트 헤드 포인터

// 인접 리스트에 간선 추가
void add_edge(int from, int to) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = to;              // 연결된 정점 정보 저장
    newNode->next = adj[from];        // 기존 리스트에 이어붙이기
    adj[from] = newNode;              // 리스트의 head 갱신
}

// 그래프(지도) 빌드
void build_graph() {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (map[y][x] != 'L') continue;
            int v = y * W + x;

            int dx[4] = {0, 0, -1, 1};
            int dy[4] = {-1, 1, 0, 0};

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d];
                int nx = x + dx[d];

                if (ny < 0 || ny >= H || nx < 0 || nx >= W) continue;
                if (map[ny][nx] != 'L') continue;

                int u = ny * W + nx;
                add_edge(v, u);  // v → u 연결
            }
        }
    }
}

// 디버그용: 인접 리스트 출력
void print_graph() {
    for (int i = 0; i < H * W; i++) {
        if (adj[i]) {
            printf("정점 %d와 연결된 정점들: ", i);
            Node* cur = adj[i];
            while (cur) {
                printf("%d ", cur->vertex);
                cur = cur->next;
            }
            printf("\n");
        }
    }
}

// 메모리 해제
void free_graph() {
    for (int i = 0; i < H * W; i++) {
        Node* cur = adj[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

int main() {
    scanf("%d %d", &H, &W);
    for (int i = 0; i < H; i++) {
        scanf("%s", map[i]);
    }

    build_graph();  // 지도 → 인접 리스트로 그래프 생성
    print_graph();  // 연결 상태 확인

    free_graph();   // 메모리 정리
    return 0;
}