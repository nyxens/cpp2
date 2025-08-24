#include <iostream>
#include <vector>
using namespace std;
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
int main(){
    vector<int> a = {38, 27, 43, 3, 9, 82, 10}; 
    int n = a.size();
    quicksort(a, 0, n - 1);
    cout << "Sorted array: ";
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}       