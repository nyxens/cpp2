#include <iostream>
#include <vector>
using namespace std;
int manhattan(vector<int>& a,vector<int>& b){
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}
int mincost(vector<vector<int>>& points){
    int n = points.size();
    vector<int> minDist(n,999999);
    vector<bool> inMST(n,false);
    int result = 0;
    minDist[0] = 0;
    for(int i = 0; i < n; i++){
        int u = -1;
        for(int j = 0; j < n; j++){
            if(!inMST[j] && (u == -1 || minDist[j] < minDist[u])){
                u = j;
            }
        }
        result += minDist[u];
        inMST[u] = true;
        for(int v = 0; v < n; v++){
            if(!inMST[v]){
                int dist = manhattan(points[u],points[v]);
                minDist[v] = min(minDist[v],dist);
            }
        }
    }
    return result;
}
int main() {
    vector<vector<int>> points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << mincost(points) << endl;
    return 0;
}