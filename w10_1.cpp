#include<iostream>
#include<vector>
using namespace std;
double Min=9999999999;
void printdp(vector<int> &dp,int n){
    cout<<"Assignment: ";
    for(int i=0;i<n;i++)
      cout<<dp[i]<<" ";
    cout<<endl;
}
void calculation(vector<int> &dp,vector<pair<int,pair<int,double>>> node,int n,int m){
    vector<double> temparature(n);
    for(int i=0;i<n;i++){
        temparature[i]=1+((dp[i])*0.2);
    }
    for(int i=0;i<m;i++){
        node[i].second.second=node[i].second.second*(temparature[node[i].first]*temparature[node[i].second.first]);
    }
    for(int i=0;i<m;i++){
        cout<<node[i].second.second<<" ";
    }
    cout<<endl;
    vector<vector<double>> a(n,vector<double>(n,1e9));
    for(int i=0;i<m;i++){
        a[node[i].first][node[i].second.first]=node[i].second.second;
        a[node[i].second.first][node[i].first]=node[i].second.second;
    }
    for(int i=0;i<n;i++)
      a[i][i]=0;
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[i][k]!=1e9&&a[k][j]!=1e9)
                  a[i][j]=min(a[i][k]+a[k][j],a[i][j]);
            }
        }
    }
    double m1=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            m1+=a[i][j];
        }
    }
    Min=min(m1,Min);
}
bool safe(vector<vector<int>> &b,int r,int c,int n){
    for(int i=0;i<r;i++) 
      if(b[i][c]==1) 
       return false;
    for(int i=r-1,j=c-1;i>=0&&j>=0;i--,j--) 
       if(b[i][j]==1) 
         return false;
    for(int i=r-1,j=c+1;i>=0&&j<n;i--,j++) 
       if(b[i][j]==1) 
         return false;
    return true;
}
bool solve(vector<vector<int>> &b,int r,int n,vector<int> &dp,vector<pair<int,pair<int,double>>> &node,int m){
    if(r==n){
      printdp(dp,n);
      calculation(dp,node,n,m);
     return false;
    }
    for(int c=0;c<n;c++){
        if(safe(b,r,c,n)){
            b[r][c]=1;
            dp[r]=c;
            solve(b,r+1,n,dp,node,m);
            dp[r]=0;
            b[r][c]=0;
        }
    }
    return false;
}
int main(){
    int n=4;
    int m=5;
 vector<pair<int,pair<int,double>>> node(m);
    node[0]={0,{1,10}};
    node[1]={1,{2,15}};
    node[2]={2,{3,10}};
    node[3]={3,{0,20}};
    node[4]={1,{3,25}};
    vector<vector<int>> b(4,vector<int>(4));
    vector<int>dp(n,0);
    solve(b,0,n,dp,node,m);
    cout<<"The minimum distance is:"<<Min<<endl;
}