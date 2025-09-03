#include <bits/stdc++.h>
using namespace std;
#define INF 99999

void printMatrix(vector<vector<int>> &dist, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "----------------------\n";
}

// Reconstruct path using the next matrix
vector<int> getPath(int u, int v, vector<vector<int>> &Next) {
    if (Next[u][v] == -1) return {}; // no path
    vector<int> path = {u};
    while (u != v) {
        u = Next[u][v];
        path.push_back(u);
    }
    return path;
}

void floydWarshall(vector<vector<int>> &graph, int n, int src, int dest) {
    vector<vector<int>> dist = graph;
    vector<vector<int>> Next(n, vector<int>(n, -1));

    // Initialize Next matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != INF && i != j)
                Next[i][j] = j;
        }
    }

    cout << "Initial matrix:\n";
    printMatrix(dist, n);

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF
                    && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    Next[i][j] = Next[i][k];  // update path
                }
            }
        }
        cout << "After including vertex " << k << ":\n";
        printMatrix(dist, n);
    }

    // Print shortest distance
    if (dist[src][dest] == INF) {
        cout << "No path exists from " << src+1 << " to " << dest+1 << "\n";
    } else {
        cout << "Shortest distance from " << src+1 << " to " << dest+1 << " = " << dist[src][dest] << "\n";
        vector<int> path = getPath(src, dest, Next);
        cout << "Path: ";
        for (int v : path) cout << v+1 << " "; // +1 to make it 1-based
        cout << "\n";
    }
}

int main() {
    int n = 7;
    vector<vector<int>> graph = {
        {0,   5, 3, INF, INF, INF, INF},
        {INF, 0,   1, 5,   2,   INF, INF},
        {INF, INF, 0, 7,   INF, INF, 12},
        {INF, INF, INF, 0, 3,   1,   2},
        {INF, INF, INF, INF, 0, 1,   INF},
        {INF, INF, INF, INF, INF, 0, 4},
        {INF, INF, INF, INF, INF, INF, 0}
    };

    floydWarshall(graph, n, 0, 6); // Find path from 1→7 (0-based indices)
    return 0;
}
