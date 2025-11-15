#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct activity{
    int start;
    int finish;
};
bool compare(activity a,activity b){
    return a.finish < b.finish;
}
void selection(vector<activity> &a){
    sort(a.begin(),a.end(),compare);
    int lastfinish = a[0].finish;
    cout << "(" << a[0].start << "," << a[0].finish << ")";
    for(int i = 0; i < a.size(); i++){
        if(a[i].start >= lastfinish){
            cout << "(" << a[i].start << "," << a[i].finish << ")";
            lastfinish = a[i].finish;
        }
    } 
}
int main(){
    int n;
    cout << "Enter number of activities: ";
    cin >> n;
    vector<activity> activities(n);
    cout << "Enter start and finish times:\n";
    for (int i = 0; i < n; i++) {
        cin >> activities[i].start >> activities[i].finish;
    }
    selection(activities);
    return 0;
}
