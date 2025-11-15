#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<vector<int>> work(vector<int> &a){
    vector<vector<int>> result;
    sort(a.begin(),a.end());
    int n = a.size();
    for(int i = 0; i<n-1;i++){
        if(i>0 && a[i]==a[i-1])// dont repeat already done dupicate index
            continue;
        int l = i+1;
        int r = n-1;
        int target = -a[i];
        while(l<r){
            int sum = a[l] + a[r];
            if(sum == target){
                result.push_back({a[i],a[l],a[r]});//save triplet
                while(l<r && a[l] == a[l+1])
                    l++;
                while(l<r && a[r] == a[r-1])
                    r--;
                l++;
                r--;
            }
            else if(sum < target)
                l++;
            else    
                r--;
        }
    }
    return result;
}
int main(){
    vector<int> input = {-1,0,1,2,-1,-4};
    vector<vector<int>> result = work(input);
    for(auto &a: result){
        cout << a[0] <<a[1] << a[2] << endl;
    }
}