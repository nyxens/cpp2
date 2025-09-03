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

void floydWarshall(vector<vector<int>> &graph, int n) {
    vector<vector<int>> dist = graph;

    cout << "Initial matrix:\n";
    printMatrix(dist, n);

    for (int k = 0; k < n; k++) {
        // Pick all vertices as intermediate
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF
                    && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
        cout << "After including vertex " << k << ":\n";
        printMatrix(dist, n);
    }
}

int main() {
    int n = 7;
    vector<vector<int>> graph = {
        {0,   5, 3,INF,INF, INF,INF},
        {INF, 0,   1, 5,2,INF, INF},
        {INF, INF, 0,   7,INF,INF,12},
        {INF, INF, INF, 0,3,1,2},
        {INF, INF, INF, INF,0,1,INF},
        {INF, INF, INF, INF,INF,0,4},
        {INF, INF, INF, INF,INF,INF,0}
    };

    floydWarshall(graph, n);
    return 0;
}
