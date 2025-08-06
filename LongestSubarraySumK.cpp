#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& a, long long k) {
        unordered_map<long long, int> prefixSumIndex;
        long long sum = 0;
        int maxLen = 0;

        for (int i = 0; i < a.size(); ++i) {
            sum += a[i];

            if (sum == k) {
                maxLen = i + 1;
            }

            if (prefixSumIndex.find(sum - k) != prefixSumIndex.end()) {
                maxLen = max(maxLen, i - prefixSumIndex[sum - k]);
            }

            // store first occurrence of prefix sum
            if (prefixSumIndex.find(sum) == prefixSumIndex.end()) {
                prefixSumIndex[sum] = i;
            }
        }

        return maxLen;
    }
};

int main() {
    vector<int> arr = {10, 5, 2, 7, 1, -10};
    long long k = 15;

    Solution sol;
    int result = sol.longestSubarray(arr, k);

    cout << "Length of longest subarray with sum " << k << " is: " << result << endl;

    return 0;
}
