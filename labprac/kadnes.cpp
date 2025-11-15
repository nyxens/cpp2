#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> input = {-2,1,-3,4,-1,2,1,-5,4};
    int currentsum = 0;
    int maxsofar = -999;
    int temp_start =0;
    int s =0 ,e=0;
    for(int i = 0;i<input.size();i++){
        currentsum += input[i];
        if(currentsum > maxsofar){
            maxsofar = currentsum;
            s = temp_start;
            e = i;
        }
        if(currentsum <0){
            currentsum =0;
            temp_start = i +1;
        }
    }
    cout << maxsofar << endl;
    for(int i = s;i<=e;i++)
        cout << input[i] << " ";
}