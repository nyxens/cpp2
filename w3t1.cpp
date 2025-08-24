#include <iostream>
#include <vector>
using namespace std;
void maxsubarray(vector<int>& arr){
    int n = arr.size();
    int max1 = 0;              
    int curr = 0;              
    int start = 0, end = -1;   
    int temp = 0;
    for(int i = 0;i < n;i++){
        curr = max(arr[i],curr + arr[i]);
        if(curr == arr[i]){
            temp = i;
        }
        if(curr > max1){
            max1 = curr;
            start = temp;
            end = i;
        }
    }
    cout << "Maximum Subarray Sum = " << max1 << endl;
    if(end == -1){
        cout << "Subarray = {}" << endl;
    }else{
        cout << "Subarray = { ";
        for(int i = start; i <= end; i++){
            cout << arr[i] << " ";
        }
        cout << "}" << endl;
    }
}
int main(){
    int N;
    cout << "Enter size of array: ";
    cin >> N;
    vector<int> arr(N);
    cout << "Enter elements: ";
    for(int i = 0;i < N;i++)
        cin >> arr[i];
    maxsubarray(arr);
}
