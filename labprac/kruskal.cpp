#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Edge{
    int u;
    int v;
    int w;
};
bool compare(Edge a, Edge b){
    return a.w < b.w;
}
vector<int> parent,rank1;
int findp(int x){
    if(parent[x] != x)
        parent[x] = findp(parent[x]);
    return parent[x];
}
void union1(int a,int b){
    int a1 = findp(a);
    int b1 = findp(b);
    if(a1 != b1){
        if(rank1[a1] < rank1[b1]){
            parent[a1] = b1;
        }else if(rank1[a1] > rank1[b1]){
            parent[b1] = a1;
        }else{
            parent[b1] = a1;
            rank1[a1]++;
        }
    }
}
int main(){
    int V = 4;
    parent.resize(V);
    rank1.resize(V,0);
    for(int i=0;i<V;i++){
        parent[i] = i;
    }
    vector<Edge> edges = {
        {0,1,10},
        {0,2,6},
        {0,3,5},
        {1,3,15},
        {2,3,4}
    };
    sort(edges.begin(),edges.end(),compare);
    int mstweight = 0;
    for(auto &e : edges){
        int u = e.u;
        int v = e.v;
        int w = e.w;
        if(findp(u) != findp(v)){
            union1(u,v);
            mstweight += w;
            cout<< u << " " << v <<endl;
        }
    }
    cout << mstweight << endl;
}