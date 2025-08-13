vector<int> superiorElements(_MSC_VER, vector<int>& arr) {
    int n = arr.size();
    vector<int> result;
    int maxFromRight = arr[n - 1];
    result.push_back(maxFromRight);

    for (int i = n - 2; i >= 0; --i) {
        if (arr[i] > maxFromRight) {
            result.push_back(arr[i]);
            maxFromRight = arr[i];
        }
    }

    // Reverse the result to maintain the order of superior elements
    reverse(result.begin(), result.end());
    return result;
}
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> arr = {3, 4, 5, 2, 1, 6};
    vector<int> result = superiorElements(arr);

    cout << "Superior elements: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}