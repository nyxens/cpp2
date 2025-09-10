#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Drone{
    int start;
    int end;
};
bool compare(Drone d1, Drone d2){
    return d1.end < d2.end;
}
int minsensor(vector<Drone> &drones){
    sort(drones.begin(), drones.end(), compare);
    int count = 1;
    int lastEnd = drones[0].end;
    for (int i = 1; i < drones.size(); i++){
        if (drones[i].start > lastEnd){
            count++;
            lastEnd = drones[i].end;
        }
    }
    return count;
}
int main(){
    vector<Drone> drones = {{1, 3}, {2, 4}, {3, 5}, {0, 6}, {5, 7}, {8, 9}};
    cout << "Minimum sensors: " << minsensor(drones) << endl;
}