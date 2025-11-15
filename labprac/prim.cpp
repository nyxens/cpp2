#include <iostream>
#include <vector>
using namespace std;
void prims(vector<vector<int>> &graph){
    int V = graph.size();
    int edgesused =0,totalweight = 0;
    vector<bool> visited(V,false);
    visited[0] = true;
    while(edgesused < V-1){
        int minwt = 999999;
        int u = -1,v=-1;
        for(int i=0;i<V;i++){
            if(visited[i]){
                for(int j =0;j<V;j++){
                    if(!visited[j] && graph[i][j] && graph[i][j] < minwt){
                        minwt = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }
        cout << u << "-" << v << ":" << minwt << endl;
        edgesused++;
        visited[v] = true;
        totalweight += minwt;
    }
    cout << totalweight << endl;
}
int main(){
    vector<vector<int>> graph = {
    {0 ,2 ,0 ,6 ,0},
    {2 ,0 ,3 ,8 ,5},
    {0 ,3 ,0 ,0 ,7},
    {6 ,8 ,0 ,0 ,9},
    {0 ,5 ,7 ,9 ,0}
    };
    prims(graph);
}