#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Item{
    int val;
    int wt;
};
bool compare(Item a,Item b){
    double r1 = (double)a.val/a.wt;
    double r2 = (double)b.val/b.wt;
    return r1 > r2;
}
int main(){
    int cap = 50;
    vector<int> values= {60,100,120};
    vector<int> weight= {10,20,30};
    int n = values.size();
    vector<Item> items(n);
    for(int i=0;i<n;i++){
        items[i] = {values[i],weight[i]};
    }
    double knap = 0;
    sort(items.begin(),items.end(),compare);
    for(int i=0;i<n;i++){
        if(cap==0 )
            break;
        if(items[i].wt <= cap){
            cap -= items[i].wt;
            knap += items[i].val;
        }else{
            double frac = (double)cap/items[i].wt;
            knap += items[i].val * frac;
            break;
        }
    }
    cout << knap << endl;

}