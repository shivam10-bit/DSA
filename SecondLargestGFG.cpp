#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int getSecondLargest(vector<int>& a) {
        int n = a.size();
        if (n < 2) return -1;
        int largest = a[0];
        int slargest = -1;
        for (int i = 1; i < n; i++) {
            if (a[i] > largest) {
                slargest = largest;
                largest = a[i];
            } else if (a[i] < largest && a[i] > slargest) {
                slargest = a[i];
            }
        }
        return slargest;
    }
};

int main() {
    vector<int> arr = {10, 20, 4, 45, 99};
    Solution ob;
    int ans = ob.getSecondLargest(arr);
    cout << "Second largest element: " << ans << endl;
    return 0;
}
