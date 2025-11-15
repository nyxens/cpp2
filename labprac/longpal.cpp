#include <iostream>
using namespace std;
string expand(string a, int l,int r){
    while(l>=0 && r<a.size() && a[l]==a[r]){
        l--;
        r++;
    }
    return a.substr(l+1,r-l-1);
}
string lgpal(string a){
    int n = a.size();
    if(n<=1)
        return a;
    string best = "";
    for(int i=0;i<n;i++){
        string p1 = expand(a,i,i);
        if(p1.size() > best.size())
            best = p1;
        string p2 = expand(a,i,i+1);
        if(p2.size() > best.size())
            best = p2;
    }
    return best;
}
int main(){
    string a = "babad";
    cout << lgpal(a) << endl;
}