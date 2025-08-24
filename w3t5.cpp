#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
using namespace std;
int linearSelect(vector<int>& arr,int left,int right,int k);
int partition(vector<int>& arr,int left,int right,int pivot){
    int i = left;
    for(int j = left; j <= right; j++){
        if(arr[j] == pivot){ 
            swap(arr[j],arr[right]); 
            break; 
        }
    }
    for(int j = left; j < right; j++){
        if(arr[j] < pivot){ 
            swap(arr[i],arr[j]); 
            i++; 
        }
    }
    swap(arr[i],arr[right]);
    return i;
}
int medianOfMedians(vector<int>& arr,int left,int right){
    int n = right - left + 1;
    if(n <= 5){
        sort(arr.begin() + left,arr.begin() + right + 1);
        return arr[left + n/2];
    }
    vector<int> medians;
    for(int i = left; i <= right; i += 5){
        int subRight = min(i+4,right);
        sort(arr.begin() + i,arr.begin() + subRight + 1);
        medians.push_back(arr[i + (subRight-i)/2]);
    }
    return linearSelect(medians,0,medians.size()-1,medians.size()/2);
}
int linearSelect(vector<int>& arr,int left,int right,int k){
    if(left == right) 
        return arr[left];
    int pivot = medianOfMedians(arr,left,right);
    int pivotIndex = partition(arr,left,right,pivot);
    if(k == pivotIndex) 
        return arr[k];
    else if(k < pivotIndex) 
        return linearSelect(arr,left,pivotIndex-1,k);
    else 
        return linearSelect(arr,pivotIndex+1,right,k);
}
vector<int> fill(int n){
    vector<int> prices(n);
    for(int i = 0; i < n; i++)
        prices[i] = 1 + rand() % 1000;// stock prices 1-1000
    return prices;
}
int main(){
    srand(time(0));
    int n;
    cout << "Enter number of days: ";
    cin >> n;
    vector<int> prices = fill(n);
    int k;
    cout << "Enter k: ";
    cin >> k;

    int kth = linearSelect(prices,0,n-1,k-1);
    int p90i = ceil(0.9*n) - 1;
    int p90 = linearSelect(prices,0,n-1,p90i);

    cout << k << "-th smallest stock price: " << kth << endl;
    cout << "90th percentile stock price: " << p90 << endl;
    return 0;
}
