#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
void findsubarray(vector<int>& nums,int k){
    int n = nums.size();
    unordered_map<int,int> first;
    unordered_map<int,int> freq;
    int prefix = 0,count = 0,maxLen = 0;
    first[0] = -1;
    freq[0] = 1;
    for(int j = 0;j < n;j++){
        prefix += nums[j];
        if(freq.find(prefix - k) != freq.end()){
            count += freq[prefix - k];
            int i = first[prefix - k];
            maxLen = max(maxLen,j - i);
        }
        if(first.find(prefix) == first.end()) 
            first[prefix] = j;
        freq[prefix]++;
    }
    if(count == 0){
        cout << 0 << endl;
    } else{
        cout << "Longest Subarray Length = " << maxLen << endl;
        cout << "Total Number of Subarrays = " << count << endl;
    }
}
int main(){
    int n,k;
    cout << "Enter size of array: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Enter elements: ";
    for(int i = 0;i < n;i++) 
        cin >> nums[i];
    cout << "Enter value of k: ";
    cin >> k;
    findsubarray(nums,k);
    return 0;
}
