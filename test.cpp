#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Partition function (Lomuto scheme)
int partition(vector<int>& a, int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1); // random pivot
    swap(a[pivotIndex], a[high]);
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

// QuickSelect: find the k-th smallest element (0-based index)
int quickSelect(vector<int>& a, int low, int high, int k) {
    while (true) {
        int pivotIndex = partition(a, low, high);
        if (pivotIndex == k) {
            return a[k]; // Found k-th smallest
        } else if (k < pivotIndex) {
            high = pivotIndex - 1; // search left
        } else {
            low = pivotIndex + 1;  // search right
        }
    }
}

int main() {
    srand(time(0));

    vector<int> arr = {7, 2, 9, 4, 1, 8, 5};
    int k = 3; // Find 4th smallest element (0-based index)

    int kthSmallest = quickSelect(arr, 0, arr.size() - 1, k);
    cout << "The " << k+1 << "-th smallest element is: " << kthSmallest << endl;

    return 0;
}
