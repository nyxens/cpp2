#include <iostream>
using namespace std;
#define INF 99999
int main(){
    int v = 9;
    int dist[v];
    bool visited[v];
    int graph[9][9] = {
        {0,4,0,0,0,0,0,8,0},
        {4,0,8,0,0,0,0,11,0},
        {0,8,0,7,0,4,0,0,2},
        {0,0,7,0,9,14,0,0,0},
        {0,0,0,9,0,10,0,0,0},
        {0,0,4,14,10,0,2,0,0},
        {0,0,0,0,0,2,0,1,6},
        {8,11,0,0,0,0,1,0,7},
        {0,0,2,0,0,0,6,7,0}
    };
    for(int i=0;i<v;i++){
        dist[i] = INF;
        visited[i] = false;
    }
    dist[0] = 0;
    for(int count = 0;count < v-1;count++){
        int u = -1;
        int mind = INF;
        for(int i=0;i<v;i++){
            if(!visited[i]&&dist[i]<mind){
                mind = dist[i];
                u = i;
            }
        }
        visited[u] = true;
        for(int i =0;i<v;i++){
            if(graph[i][u] && !visited[i] && dist[u]+graph[i][u]<dist[i])
                dist[i] = dist[u] + graph[i][u];
        }
    }
    for(int i =0;i<v;i++)
        cout << dist[i] << " " ;
}