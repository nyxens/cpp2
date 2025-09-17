#include <iostream>
#include <vector>
#include <climits>
using namespace std;
void prims(vector<vector<int>> &graph) {
    int V = graph.size();
    vector<bool> visited(V,false);
    visited[0] = true;
    int edgesUsed = 0,totalWeight = 0;
    while(edgesUsed < V - 1){
        int minWeight = INT_MAX;
        int u = -1,v = -1;
        for(int i = 0;i < V;i++){
            if(visited[i]){
                for(int j = 0;j < V;j++){
                    if(!visited[j] && graph[i][j] && graph[i][j] < minWeight){
                        minWeight = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }
        cout << "Edge: " << u << " - " << v << "  Weight: " << minWeight << endl;
        visited[v] = true;
        totalWeight += minWeight;
        edgesUsed++;
    }
    cout << "Total MST Weight = " << totalWeight << endl;
}
int main(){
    int V = 4;
    vector<vector<int>> graph = {
        {0, 10, 15, 30},
        {10, 0, 0, 40},
        {15, 0, 0, 50},
        {30, 40, 50, 0}
    };
    cout << "Prim's MST:\n";
    prims(graph);
    return 0;
}
