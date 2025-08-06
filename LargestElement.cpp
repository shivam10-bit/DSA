#include <iostream>
#include <vector>
using namespace std;

int largestElement(vector<int>& arr) {
    int largest = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }
    return largest;
}

int main() {
    vector<int> arr = {10, 5, 20, 8};
    cout << "Largest element: " << largestElement(arr) << endl;
    return 0;
}