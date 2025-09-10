#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Container{
    double val;
    double w;
};
bool compare(Container a,Container b){
    return(a.val / a.w) > (b.val / b.w);
}
double maxuse(vector<Container>& containers,int capacity){
    sort(containers.begin(),containers.end(),compare);
    double totalval = 0.0;
    for(auto c : containers){
        if(capacity >= c.w){
            totalval += c.val;
            capacity -= c.w;
        }else{
            totalval += (c.val / c.w) * capacity;
            break;
        }
    }
    return totalval;
}
int main(){
    vector<Container> containers ={{60,10},{100,20},{120,30}};
    int capacity = 50;
    cout << "Maximum usefulness: " << maxuse(containers,capacity) << endl;
    return 0;
}
