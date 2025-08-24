#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
void findzerosumsubarrays(vector<int>& nums){
    int n=nums.size();
    unordered_map<int,vector<int>> mp;
    int prefix=0;
    mp[0].push_back(-1);
    cout<<"Subarrays with sum 0:"<<endl;
    bool found=false;
    for(int j=0;j<n;j++){
        prefix+=nums[j];
        if(mp.find(prefix)!=mp.end()){
            for(int startindex:mp[prefix]){
                found=true;
                cout<<"[ ";
                for(int k=startindex+1;k<=j;k++){
                    cout<<nums[k]<<" ";
                }
                cout<<"]"<<endl;
            }
        }
        mp[prefix].push_back(j);
    }
    if(!found){
        cout<<"No subarray with sum 0 found."<<endl;
    }
}
int main(){
    int n;
    cout<<"Enter size of array: ";
    cin>>n;
    vector<int> nums(n);
    cout<<"Enter elements: ";
    for(int i=0;i<n;i++)
        cin>>nums[i];
    findzerosumsubarrays(nums);
    return 0;
}
