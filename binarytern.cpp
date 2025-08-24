#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <fstream>
using namespace std;
#define N 20
void initialize(int a[],int n){
    for(int i = 0;i < n;i++){
        a[i] = rand() % 100;
    }
}
int binarysearch(int a[],int n,int x){
    int t[N];
    int count = 0;
    copy(a,a+n,t);
    sort(t,t+n);
    int low = 0,high = n - 1;
    while(low <= high){
        count++;
        int mid =(low+high) / 2;
        if(t[mid] == x) 
            return count;
        else if(t[mid] < x) 
            low = mid+1;
        else high = mid - 1;
    }
    return count;
}
int terinaraysearch(int a[],int n,int x){
    int t[N];
    int count = 0;
    copy(a,a+n,t);
    sort(t,t+n);
    int low = 0,high = n - 1;
    while(low <= high){
        count++;
        int mid1 = low +(high - low) / 3;
        int mid2 = high -(high - low) / 3;
        if(t[mid1] == x || t[mid2] == x)
            return count;
        if(x < t[mid1])
            high = mid1 - 1;
        else if(x > t[mid2])
            low = mid2+1;
        else{
            low = mid1+1;
            high = mid2 - 1;
        }
    }
    return count;
}
int main(){
    srand(time(0));
    int a[N];
    ofstream fout("search_steps.dat");
    fout << "#Size Binary Ternary\n";
    for(int size = 1;size <= N;size++){
        for(int i = 0;i < size;i++){
            a[i] = i * 2;
        }
        int x = -1;
        int steps_bin = binarysearch(a,size,x);
        int steps_ter = terinaraysearch(a,size,x);
        fout << size << " " << steps_bin << " " << steps_ter << endl;
    }
    fout.close();
    cout << "Data written to search_steps.dat" << endl;
    return 0;
}
