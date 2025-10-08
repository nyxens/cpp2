#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int u, v;
    int w;
};
struct Compare {
    bool operator()(const Edge& a,const Edge& b){
        return a.w > b.w;
    }
};
int main() {
    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for(int i = 0; i < M; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    vector<bool> inMST(N + 1,false);
    priority_queue<Edge,vector<Edge>,Compare> pq;
    int weight = 0;
    int count = 0;
    inMST[1] = true;
    count++;
    for(auto &e : edges){
        if(e.u == 1 || e.v == 1)
            pq.push(e);
    }
    while(count < N && !pq.empty()){
        Edge curr = pq.top(); 
        pq.pop();
        int u = curr.u; 
        int v = curr.v;
        int w = curr.w;
        if(inMST[u] && inMST[v]) 
            continue;
        int newNode = inMST[u] ? v : u;
        inMST[newNode] = true;
        weight += w;
        count++;
        for(auto &e : edges){
            if((e.u == newNode && !inMST[e.v]) || (e.v == newNode && !inMST[e.u])){
                pq.push(e);
            }
        }
    }
    cout << weight << "\n";
    return 0;
}