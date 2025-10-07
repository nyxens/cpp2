#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;   
//use plot6
int partition(vector<int>& arr,int left,int right,int pivot){
    int i = left;
    for(int j = left;j <= right;j++){
        if(arr[j] == pivot){ 
            swap(arr[j],arr[right]);
            break;
        }
    }
    for(int j = left;j < right;j++){
        if(arr[j] < pivot){ 
            swap(arr[i],arr[j]);
            i++;
        }
    }
    swap(arr[i],arr[right]);
    return i;
}
int linearSelect(vector<int>& arr,int left,int right,int k);//not declared in scope lol
int medianOfMedians(vector<int>& arr,int left,int right){
    int n = right - left + 1;
    if(n <= 5){
        sort(arr.begin() + left,arr.begin() + right + 1);
        return arr[left + n/2];
    }
    vector<int> medians;
    for(int i = left;i <= right;i += 5){
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
vector<int> fillrand(int n){
    vector<int> prices(n);
    for(int i = 0;i < n;i++)
        prices[i] = 1 + rand() % 10000;
    return prices;
}
int main(){
    srand(time(0));
    vector<int> sizes ={100000,200000,500000,800000,1000000};
    ofstream outFile("timing_data.dat");  //outFile or fout
    outFile << "#Size LinearTime SortingTime\n";
    for(int n : sizes){
        vector<int> prices = fillrand(n);
        vector<int> arr1 = prices;
        auto start1 = high_resolution_clock::now();
        int k = n/2;
        int median = linearSelect(arr1,0,n-1,k);
        auto end1 = high_resolution_clock::now();
        double linearTime = duration<double,milli>(end1 - start1).count();

        vector<int> arr2 = prices;
        auto start2 = high_resolution_clock::now();
        sort(arr2.begin(),arr2.end());
        int median2 = arr2[k];
        auto end2 = high_resolution_clock::now();
        double sortingTime = duration<double,milli>(end2 - start2).count();

        outFile << n << " " << linearTime << " " << sortingTime << "\n";
    }
    outFile.close();
    cout << "Timing data saved to timing_data.dat\n";
    return 0;
}
