#include <bits/stdc++.h>
using namespace std;
int main(){
    int N, M;
    double alpha;
    cin >> N >> M >> alpha;
    vector<vector<pair<int,pair<double,int>>>> adj(N + 1);
    for(int i = 0; i < M; i++){
        int u,v,t;
        double p;
        cin >> u >> v >> t >> p;
        double priority = -log(p) + alpha * t;
        adj[u].push_back({v,{priority,t}});
    }
    const double INF = 1e18;
    vector<double> prioarr(N+1,INF);
    vector<int> timetaken(N+1,INT_MAX);
    //(currentprioarrance,node) basically means smallest prio comes out first
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> pq;
    prioarr[1] = 0;
    timetaken[1] = 0;
    pq.push(make_pair(0.0,1)); 

    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();
        double currprioarr = top.first;
        int u = top.second;
        if(currprioarr > prioarr[u]) 
            continue;
        for(int i = 0; i < adj[u].size(); i++){

            int v = adj[u][i].first;
            double priority = adj[u][i].second.first;
            int t = adj[u][i].second.second;

            double newprioarr = prioarr[u] + priority;
            int newTime = timetaken[u] + t;

            if(newprioarr < prioarr[v]){
                prioarr[v] = newprioarr;
                timetaken[v] = newTime;
                pq.push(make_pair(newprioarr,v));
            }
        }
    }
    if(prioarr[N] == INF)
        cout << -1;
    else
        cout << setprecision(6) << prioarr[N] << " " << timetaken[N];
    return 0;
}