#include <iostream>
using namespace std;
int main(){
    int value[] = {60,100,120};
    int weight[] = {10,20,30};
    int cap = 50;
    int n = 3;
    int dp[n+1][cap+1];
    for(int i=0;i<=n;i++){
        for(int w=0;w<=cap;w++){
            if(i==0||w==0)
                dp[i][w] = 0;
            else if(weight[i-1]<=w){
                dp[i][w] = max(dp[i-1][w],value[i-1]+dp[i-1][w-weight[i-1]]);//here exculude case can be 
                //got from dp table include means ith item in dp table is i-1 index in value and weight
            }
            else{
                dp[i][w]= dp[i-1][w];
            }
        }
    }
    cout << dp[n][cap] << endl;
}