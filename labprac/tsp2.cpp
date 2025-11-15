#include<bits/stdc++.h>
using namespace std;
int tsp(vector<vector<int>> &dp,vector<vector<int>> &cost,int pos,int mask){
    int n=cost.size();
    int visited_all=(1<<n)-1;
    if(mask==visited_all)
        return cost[pos][0];
    if(dp[mask][pos] != -1)
        return dp[mask][pos];
    int min_r =INT_MAX, r=INT_MAX;
    dp[mask][pos]=INT_MAX;
    for(int i=0;i<n;i++){ //try all cities i 0 to n-1
        if((mask&(1<<i)) == 0){ //bit i is not visited
            r = cost[pos][i] + tsp(dp,cost,i, mask|1<<i); //updated mask with i now visied
            min_r = min (r, min_r);
        }
    }
    return dp[mask][pos] = min_r;
}
int main(){
  vector<vector<int>> cost = {
    {0, 29, 82, 46, 68},
    {29, 0, 55, 63, 23},
    {82, 55, 0, 14, 52},
    {46, 63, 14, 0, 31},
    {68, 23, 52, 31, 0}
};
   int n=cost.size();
   vector<vector<int>> dp(1<<n,vector<int>(n,-1));
   int c=tsp(dp,cost,0,0);
   cout<<"The minimum cost is:"<<c<<endl;
}