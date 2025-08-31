#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int n, m; // n = processes, m = resources
int adj[MAX][MAX]; // adjacency matrix
bool visited[MAX];
bool recStack[MAX];

bool isCyclicUtil(int v) {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        for (int i = 0; i < n+m; i++) {
            if (adj[v][i]) {
                if (!visited[i] && isCyclicUtil(i))
                    return true;
                else if (recStack[i])
                    return true;
            }
        }
    }
    recStack[v] = false;
    return false;
}

bool isDeadlock() {
    for (int i = 0; i < n+m; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < n; i++) {
        if (isCyclicUtil(i))
            return true;
    }
    return false;
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Initialize adjacency matrix
    for (int i = 0; i < n+m; i++)
        for (int j = 0; j < n+m; j++)
            adj[i][j] = 0;

    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (format: u v) \n");
    printf("u = process 0..n-1, v = resource n..n+m-1 for request\n");
    printf("v = process 0..n-1, u = resource n..n+m-1 for allocation\n");

    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1; // edge u -> v
    }

    if (isDeadlock())
        printf("Deadlock detected!\n");
    else
        printf("No deadlock.\n");

    return 0;
}
