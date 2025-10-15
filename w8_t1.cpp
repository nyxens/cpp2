#include <iostream>
#include <vector>
#include <climits>
using namespace std;
double dp[50][50];
int minindex[50][50];
string output(int i,int j){
    if(i == j)
        return "M" + to_string(i);
    return "(" + output(i,minindex[i][j]) + "x" + output(minindex[i][j] + 1, j) + ")";
}
int main() {
    int n;
    cout << "enter n : ";
    cin >> n;
    vector<int> p(n+1);
    vector<double> T(n+1);
    cout << "enter p : ";
    for(int i = 0;i <= n;i++){
        cin >> p[i];
    }
    cout << "enter T : ";
    for(int i = 1;i <= n;i++){   
        cin >> T[i];
    }
    for(int i=1;i<=n;i++){
        dp[i][i]=0;
    }
    for(int L = 2; L <= n; L++){
        for(int i = 1;i <= n-L+1;i++){
            int j = i+L-1;
            dp[i][j] = INT_MAX;
            for(int k = i; k < j; k++){
                double cost = dp[i][k]+dp[k+1][j]+(p[i-1]*p[k]*p[j])*((T[i]+T[j])/2.0);
                if(cost < dp[i][j]){
                    dp[i][j] = cost;
                    minindex[i][j] = k;
                }
            }
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cout << dp[i+1][j+1] << " ";
        }
        cout << endl;
    }
    cout << "Minimum Energy Cost: " << dp[1][n] << endl;
    cout << "Optimal Order: " << output(1,n) << endl;
    return 0;
}