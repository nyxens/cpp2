#include <iostream>
#include <vector>
using namespace std;
void merge(vector<int> &a,int s,int m,int e){
    vector<int> temp;
    int i=s,j=m+1;
    while(i<=m && j<=e)
        if(a[i] <= a[j]){
            temp.push_back(a[i++]);
        }else{
            temp.push_back(a[j++]);
        }
    while(i <= m)
        temp.push_back(a[i++]);
    while(j <= e)
        temp.push_back(a[j++]);
    for(int k = 0; k < temp.size(); k++){
        a[s+k] = temp[k];
    }
}
void mergesort(vector<int> &a, int s, int e){
    if(s<e){
        int m = (s + e) / 2;
        mergesort(a,s,m);
        mergesort(a,m+1,e);
        merge(a,s,m,e);
    }
}
int main(){
    vector<int> a = {5,3,8,4,2};
    int n = a.size();
    mergesort(a,0,n-1);
    for(int i= 0;i < n;i++)
        cout << a[i] << " ";
}