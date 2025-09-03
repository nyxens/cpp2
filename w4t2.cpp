#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
//use plot8
using namespace std;
using namespace std::chrono;
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
int part(vector<int>& a,int s,int e){
    int pvt=a[e];
    int i=s-1;
    for(int j=s;j<e;j++){
        if(a[j]<=pvt){
            i++;
            swap(a[i],a[j]);
        }
    }
    i++;
    swap(a[i],a[e]);
    return i;
}
void quicksort(vector<int>& a,int s,int e){
    if(s<e){
        int p=part(a,s,e);
        quicksort(a,s,p-1);
        quicksort(a,p+1,e);
    }   
}
void fillrand(vector<int>& a){
    for(auto& val : a)
        val = rand() % 1000;
}
int main(){
    srand(time(0));
    ofstream fout("qmhsort.dat");
    fout << "# Size Quick Merge Hybrid\n";
    for(int n = 1000; n <= 50000; n += 1000){
        vector<int> a(n),b(n),c(n);
        fillrand(a);
        b = c = a;

        auto t1 = high_resolution_clock::now();
        quicksort(a,0,n-1);
        auto t2 = high_resolution_clock::now();
        auto tq = duration_cast<microseconds>(t2 - t1).count();
        
        t1 = high_resolution_clock::now();
        mergesort(b,0,n-1);
        t2 = high_resolution_clock::now();
        auto tm = duration_cast<microseconds>(t2 - t1).count();

        t1 = high_resolution_clock::now();
        sort(c.begin(), c.end());
        t2 = high_resolution_clock::now();
        auto th = duration_cast<microseconds>(t2 - t1).count();

        fout << n << " " << tq << " " << tm << " " << th << "\n";
    }
    fout.close();
    cout << "data saved to qmhsort.dat\n";
    return 0;
}