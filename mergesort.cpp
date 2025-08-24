#include <iostream>
#include <vector>
using namespace std;
void merge(vector<int>& a,int s,int mid,int e){
    vector<int> temp;
    int i = s;
    int j = mid + 1;
    while(i <= mid && j <= e){
        if(a[i] <= a[j]){
            temp.push_back(a[i++]);
        }else{
            temp.push_back(a[j++]);
        }
    }
    while(i <= mid){
        temp.push_back(a[i++]);
    }
    while(j <= e){
        temp.push_back(a[j++]);
    }
    for(int k = 0;k < temp.size();k++){
        a[s+k] = temp[k];
    }
}
void mergesort(vector<int>& a,int s,int e){
    if(s<e){
        int mid = s+(e-s)/2;
        mergesort(a,s,mid);
        mergesort(a,mid+1,e);
        merge(a,s,mid,e);
    }
}
int main(){
    vector<int> a = {38, 27, 43, 3, 9, 82, 10};
    int n = a.size();
    mergesort(a, 0, n - 1);
    cout << "Sorted array: ";
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}