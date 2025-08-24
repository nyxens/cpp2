#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;
#define N 10
int k = 9;
void initialize(int a[],int n){
    for(int i = 0;i < n;i++){
        a[i] = rand() % 100;
    }
}
void printarr(int a[],int n){
    for(int i = 0;i < n;i++){
        cout << a[i] << " ";
    }
    cout << endl;
}
void insert(int a[],int x,int p){
  if(k >= N){
        cout << "Array is full!" << endl;
        return;
    }
    if(p < 0 || p > k){
        cout << "Invalid position!" << endl;
        return;
    }
    for(int i = k;i > p;i--){
        a[i] = a[i-1];
    }
    a[p] = x;
    k++;
}
void deletepos(int a[],int p){
    if(p < 0 || p >= k){
        cout << "Invalid position!" << endl;
        return;
    }
    for(int i = p;i < k-1;i++){
        a[i] = a[i+1];
    }
    k--;
}
void deletex(int a[],int x){
    int y = -1;
    for(int i = 0;i < k;i++){
        if(a[i] == x){
            y = i;
            break;
        }
    }
    if(y == -1){
        cout << "Element not found!" << endl;
        return;
    }
    deletepos(a,y);
}
int binarysearch(int a[],int x){
    int t[N];
    int count = 0;
    copy(a,a+k,t);
    sort(t,t+k);       
    int low = 0,high = k-1;
    while(low <= high){
        count++;
        int mid = (low+high)/2;
        if (t[mid] == x){
            cout << x << " is found " << endl;
            return count;
        }
        else if (t[mid] < x)
            low = mid+1;
        else
            high = mid-1;
    }
    cout << x << " not found!" << endl;
    return count;
}
int terinaraysearch(int a[],int x){
    int t[N];
    int count = 0;
    copy(a,a+k,t);
    sort(t,t+k);       
    int low = 0,high = k-1;
    while(low <= high){
        count++;
        int mid1 = low+(high-low)/3;
        int mid2 = high-(high-low)/3;
        if(t[mid1] == x){
            cout << x << " is found " << endl;
            return count;
        }
        if(t[mid2] == x){
            cout << x << " is found " << endl;
            return count;
        }
        if(x < t[mid1])
            high = mid1-1;
        else if(x > t[mid2])
            low = mid2+1;
        else{
            low = mid1+1;
            high = mid2-1;
        }
    }
    cout << x << " not found!" << endl;
    return count;
}
void destroy(){
    k = 0;
}
int main(){
    srand(time(0));
    int a[N];
    initialize(a,k);
    cout << "Array: ";
    printarr(a,k);
    insert(a,69,3);
    cout << "Array: ";
    printarr(a,k);
    deletepos(a,4);
    cout << "Array: ";
    printarr(a,k);
    deletex(a,69);
    cout << "Array: ";
    printarr(a,k);
    int x = 50;
    int z = binarysearch(a,x);
    int e = terinaraysearch(a,x);
    destroy();
}