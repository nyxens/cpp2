#include <bits/stdc++.h>
using namespace std;

int main() {
    int cost[4][4] = {
        {0,10,15,20},
        {10,0,35,25},
        {15,35,0,30},
        {20,25,30,0}
    };

    int n = 4;
    int FULL = 1<<n;

    vector<vector<int>> dp(FULL, vector<int>(n, 1e9));

    dp[1][0] = 0; // only city 0 visited, ending at 0
    for(int mask=0; mask<FULL; mask++){
        for(int j=0; j<n; j++){
            if(!(mask & (1<<j))) 
                continue;
            for(int k=0; k<n; k++){
                if(mask & (1<<k)) 
                    continue;
                int nextMask = mask | (1<<k);
                dp[nextMask][k] = min(
                    dp[nextMask][k],
                    dp[mask][j] + cost[j][k]
                );
            }
        }
    }
    int ans = 1e9;
    for(int j=1; j<n; j++)
        ans = min(ans, dp[FULL-1][j] + cost[j][0]);
    cout << "Minimum Cost = " << ans << endl;
}
