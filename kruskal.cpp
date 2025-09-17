#include <bits/stdc++.h>
using namespace std;
vector<int> parent, rankDS;
int find(int x){
    if(parent[x] != x) 
        parent[x] = find(parent[x]);
    return parent[x];
}
void unite(int x, int y){
    int xr = find(x);
    int yr = find(y);
    if(xr == yr) 
        return;
    if(rankDS[xr] < rankDS[yr])
        parent[xr] = yr;
    else if(rankDS[xr] > rankDS[yr])
        parent[yr] = xr;
    else{
        parent[yr] = xr;
        rankDS[xr]++;
    }
}
int main(){
    int V = 4;
    vector<tuple<int,int,int>> edges = {
    {10, 0, 1},//weight,u,v
    {15, 0, 2},
    {30, 0, 3},
    {40, 1, 3},
    {50, 2, 3}
    };
    sort(edges.begin(), edges.end());
    parent.resize(V);
    rankDS.assign(V,0);
    for(int i=0;i<V;i++) 
        parent[i]=i;
    int mstWeight = 0;
    cout << "Kruskal's MST:\n";  
    for(int i=0;i<edges.size();i++){
        int w = get<0>(edges[i]);
        int u = get<1>(edges[i]);
        int v = get<2>(edges[i]);
        if(find(u) != find(v)){
            cout << u << " - " << v << " (weight " << w << ")\n";
            mstWeight += w;
            unite(u,v);
        }
    }
    cout << "Total MST Weight = " << mstWeight << endl;
    return 0;
}
