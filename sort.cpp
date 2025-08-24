#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;
void insertionsort(vector<int>& a){
    for(int i = 1;i < a.size();i++){
        int current = a[i];
        int j = i - 1;
        while(j >= 0 && a[j] > current){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = current;
    }
}
void merge(vector<int>& a,int s,int mid,int e){
    vector<int> temp;
    int i = s;
    int j = mid + 1;
    while(i <= mid && j <= e){
        if(a[i] <= a[j]) 
            temp.push_back(a[i++]);
        else 
            temp.push_back(a[j++]);
    }
    while(i <= mid) 
        temp.push_back(a[i++]);
    while(j <= e) 
        temp.push_back(a[j++]);
    for(int k = 0;k < temp.size();k++)
        a[s + k] = temp[k];
}
void mergesort(vector<int>& a,int s,int e){
    if(s < e){
        int mid = s +(e - s) / 2;
        mergesort(a,s,mid);
        mergesort(a,mid + 1,e);
        merge(a,s,mid,e);
    }
}
int partition(vector<int>& a,int s,int e){
    int pivot = a[e];
    int i = s - 1;
    for(int j = s;j < e;j++){
        if(a[j] <= pivot){
            i++;
            swap(a[i],a[j]);
        }
    }
    i++;
    swap(a[i],a[e]);
    return i;
}
void quicksort(vector<int>& a,int s,int e){
    if(s < e){
        int pi = partition(a,s,e);
        quicksort(a,s,pi - 1);
        quicksort(a,pi + 1,e);
    }
}
void fillrand(vector<int>& a){
    for(auto& val : a)
        val = rand() % 1000;
}
int main(){
    srand(time(0));
    ofstream fout("data.dat");
    fout << "# Size Insertion Merge Quick\n";
    for(int n = 50; n <= 2000; n += 50){
        vector<int> a(n),b(n),c(n);
        fillrand(a);
        b = c = a;
        
        auto t1 = high_resolution_clock::now();
        insertionsort(a);
        auto t2 = high_resolution_clock::now();
        auto ti = duration_cast<microseconds>(t2 - t1).count();

        t1 = high_resolution_clock::now();
        mergesort(b,0,n - 1);
        t2 = high_resolution_clock::now();
        auto tm = duration_cast<microseconds>(t2 - t1).count();

        t1 = high_resolution_clock::now();
        quicksort(c,0,n - 1);
        t2 = high_resolution_clock::now();
        auto tq = duration_cast<microseconds>(t2 - t1).count();

        fout << n << " " << ti << " " << tm << " " << tq << "\n";
    }
    fout.close();
    cout << "data saved to data.dat\n";
    return 0;
}
