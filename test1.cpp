#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int med(vector<int>& arr,int low ,int high){
    sort(arr.begin()+low,arr.begin()+high+1);
    int n = high - low + 1;
    return arr[low + n/2];
}
int part(vector<int>& arr,int low,int high,int pvt){
    int pvti = low;
    for(;pvti <= high; pvti++){
        if(arr[pvti] == pvt)
            break;
    swap(arr[pvti],arr[high]);
    int i = low - 1;
    for(int j = low;j < high; j++){
        if (arr[j] <= pvt){
            i++;
            swap(arr[i],arr[j]);
        }
    i++;
    swap(arr[i],arr[high]);
    return i;
    }
    }
}
int select2(vector<int>& arr,int k,int low,int high){
    int n = high - low +1;
    if(n <= 5){
        sort(arr.begin()+low,arr.begin()+high+1);
        return arr[low + k -1];
    }
    vector<int> medians;
    for(int i=low; i <= high; i += 5){
        int rightend = min(i+4,high);
        medians.push_back(med(arr,i,rightend));
    }
    int pvt = select2(medians,(medians.size()+1)/2,0,medians.size()-1);
    int j = part(arr,low,high,pvt);
    int rank = j - low + 1;
    if(rank == k)
        return arr[j];
    if(k < rank)
        return select2(arr,k,low,j-1);
    else
        return select2(arr,k-rank,j+1,high);

}
int main(){
    vector<int> arr = {12, 3, 5, 7, 4, 19, 26};
    int k = 4;
    int kthSmallest = select2(arr, k, 0, arr.size() - 1);
    cout << "The " << k << "-th smallest element is: " << kthSmallest << endl;
    return 0;
}