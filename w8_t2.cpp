#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Item{
    int val;
    int w;
    int f;
};
int n,W,F;
vector<Item> items;
vector<vector<vector<int>>> dp;
vector<vector<vector<int>>> choice;
int knap(int i,int w,int f){
    if(i == 0||w <= 0||f <= 0) 
        return 0;
    if(dp[i][w][f] != -1)
        return dp[i][w][f];
    int exclude = knap(i-1,w,f);
    int include = 0;
    if(w >= items[i].w && f >= items[i].f)
        include = items[i].val+knap(i-1,w-items[i].w,f-items[i].f);
    if(include > exclude){
        dp[i][w][f] = include;
        choice[i][w][f] = 1;
    }
    else{
        dp[i][w][f] = exclude;
        choice[i][w][f] = 0;
    }
    return dp[i][w][f];
}
int main(){
    cout << "Enter number of modules: ";
    cin >> n;
    items.resize(n+1);
    cout << "Enter value,weight,fragility for each module:" << endl;
    for(int i = 1; i <= n; i++)
        cin >> items[i].val >> items[i].w >> items[i].f;
    cout << "Enter max Weight and Fragility: ";
    cin >> W >> F;
    dp.assign(n+1,vector<vector<int>>(W+1,vector<int>(F+1,-1)));
    choice.assign(n+1,vector<vector<int>>(W+1,vector<int>(F+1,0)));
    int maxVal = knap(n,W,F);
    vector<int> selected;
    int w = W,f = F;
    for(int i = n; i >= 1; i--){
        if(choice[i][w][f] == 1){
            selected.push_back(i);
            w -= items[i].w;
            f -= items[i].f;
        }
    }
    reverse(selected.begin(),selected.end());
    cout << "\nMaximum Value: " << maxVal << endl;
    cout << "Items Selected: ";
    for(int id : selected) 
        cout << id << " ";
    cout << endl;
    return 0;
}
