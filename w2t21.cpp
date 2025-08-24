#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
//use plot4
using namespace std::chrono;
using namespace std;
int part1(vector<int>& a,int s,int e){
    int pvti = s + rand() % (e - s + 1);
    swap(a[pvti], a[e]);
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
void rquicksort(vector<int>& a,int s,int e){
    if(s<e){
        int p=part1(a,s,e);
        rquicksort(a,s,p-1);
        rquicksort(a,p+1,e);
    } 
}
void quicksort(vector<int>& a,int s,int e){
    if(s<e){
        int p=part(a,s,e);
        quicksort(a,s,p-1);
        quicksort(a,p+1,e);
    }   
}
void fill(vector<int>& a){
    for(auto& val : a)
        val = rand() % 1000;
    sort(a.begin(), a.end());
}
int main(){
    srand(time(0));
    ofstream fout("qsort.dat");
    fout << "# Size Quick RQuick\n";
    for(int n = 1000; n <= 20000; n += 1000){
        vector<int> a(n),b(n);
        fill(a);
        b = a;

        auto t1 = high_resolution_clock::now();
        quicksort(a,0,n-1);
        auto t2 = high_resolution_clock::now();
        auto tb = duration_cast<nanoseconds>(t2 - t1).count();
        
        t1 = high_resolution_clock::now();
        rquicksort(b,0,n-1);
        t2 = high_resolution_clock::now();
        auto ts = duration_cast<nanoseconds>(t2 - t1).count();

        fout << n << " " << tb << " " << ts << "\n";
    }
    fout.close();
    cout << "data saved to qsort.dat\n";
    return 0;
}    