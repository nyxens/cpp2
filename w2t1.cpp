#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
//use plot2
using namespace std;
using namespace std::chrono;
void bubblesort(vector<int>& a){
    for(int i=0 ; i<a.size() - 1 ; i++){
        for(int j=0 ; j<a.size() - i-1 ; j++){
            if(a[j] > a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}
void selectionsort(vector<int>& a){
    for(int i=0 ; i<a.size()-1 ; i++){
        int SI = i;
        for(int j=i+1 ; j<a.size() ; j++){
            if(a[j]<a[SI])
                SI=j;
        }
        swap(a[i],a[SI]);
    }
}
void heapify(vector<int> &a,int n,int i){
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if(left < n && a[left] > a[largest])
        largest = left;
    if(right < n && a[right] > a[largest])
        largest = right;
    if(largest != i){
        swap(a[i],a[largest]);
        heapify(a,n,largest);
    }
}
void heapsort(vector<int> &a){
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a,n,i);
    for (int i = n - 1; i > 0; i--){
        swap(a[0],a[i]);  
        heapify(a,i,0);    
    }
}
void fillrand(vector<int>& a){
    for(auto& val : a)
        val = rand() % 1000;
}
int main(){
    srand(time(0));
    ofstream fout("bshsort.dat");
    fout << "# Size Bubble Selection Heap\n";
    for(int n = 1000; n <= 20000; n += 1000){
        vector<int> a(n),b(n),c(n);
        fillrand(a);
        b = c = a;

        auto t1 = high_resolution_clock::now();
        bubblesort(a);
        auto t2 = high_resolution_clock::now();
        auto tb = duration_cast<microseconds>(t2 - t1).count();
        
        t1 = high_resolution_clock::now();
        selectionsort(b);
        t2 = high_resolution_clock::now();
        auto ts = duration_cast<microseconds>(t2 - t1).count();

        t1 = high_resolution_clock::now();
        heapsort(a);
        t2 = high_resolution_clock::now();
        auto th = duration_cast<microseconds>(t2 - t1).count();

        fout << n << " " << tb << " " << ts << " " << th << "\n";
    }
    fout.close();
    cout << "data saved to bshsort.dat\n";
    return 0;
}