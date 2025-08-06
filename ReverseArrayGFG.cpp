#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void reverseArray(vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            // Swap elements at left and right
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
};

int main() {
    Solution ob;

    vector<vector<int>> testCases = {
        {1, 4, 3, 2, 6, 5},
        {4, 5, 2},
        {1}
    };

    for (auto arr : testCases) {
        ob.reverseArray(arr);
        for (int num : arr)
            cout << num << " ";
        cout << endl;
    }

    return 0;
}
