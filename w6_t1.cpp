#include <iostream>
#include <vector>
using namespace std;
void dfs(vector<vector<int>>& grid,int i,int j){
    int m = grid.size();
    int n = grid[0].size();
    if(i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0) 
        return;
    grid[i][j] = 0;
    dfs(grid,i+1,j);
    dfs(grid,i-1,j);
    dfs(grid,i,j+1);
    dfs(grid,i,j-1);
}
int island(vector<vector<int>>& grid){
    int m = grid.size();
    int n = grid[0].size();
    int count = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 1){
                count++;
                dfs(grid,i,j);
            }
        }
    }
    return count;
}
int main() {
    vector<vector<int>> grid = {
        {1,1,1,1,0},
        {1,1,0,1,0},
        {1,1,0,0,0},
        {0,0,0,0,0}
    };
    cout << island(grid) << endl;
    return 0;
}
