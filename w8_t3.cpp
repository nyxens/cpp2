#include<iostream>
#include<vector>
#include<climits>
#include<cmath>
using namespace std;
double tsp(vector<vector<int>> &d,vector<int> &t,vector<int> &a,vector<vector<double>> &dp,int n,int mask,int pos){
   int visited_All=(1<<n)-1;
   double ans=1e9;
   if(mask==visited_All){
    return ((d[pos][0]*(1+(0.02*abs(t[pos]-t[0]))))+(0.5*abs(a[pos]-a[0])));
   }
   if(dp[mask][pos]!=-1){
    return dp[mask][pos];
   }
   for(int city=0;city<n;city++){
      if(((1<<city)&mask)==0){
        double newAns=((d[pos][city]*(1+(0.02*abs(t[pos]-t[city]))))+(0.5*abs(a[pos]-a[city])))+tsp(d,t,a,dp,n,mask|(1<<city),city);        
        ans=min(newAns,ans);
      }
   }
   return dp[mask][pos]=ans;
}
int main(){
    int n;
    cout<<"Enter the size:";
    cin>>n;
    vector<vector<int>> dis(n,vector<int> (n,INT_MAX));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<"enter "<<i+1<<j+1<<" element:";
            cin>>dis[i][j];
        }
    }
    vector<vector<double>> dp(1<<n,vector<double>(n,-1.0));
    vector<int> temparature(n);
    for(int i=0;i<n;i++){
        cout<<"Enter the temparature:";
        cin>>temparature[i];
    }
    vector<int> alt(n);
    for(int i=0;i<n;i++){
        cout<<"Enter the altitude:";
        cin>>alt[i];
    }
    cout<<"the minimum energy is:"<<tsp(dis,temparature,alt,dp,n,1,0)<<endl;
    return 0;
}