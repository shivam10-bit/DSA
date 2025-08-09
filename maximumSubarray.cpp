class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // Initialize 'maxi' with the first element,
        // or a very small number if the array can be empty.
        // Using INT_MIN is safer if negative numbers are possible.
        long long sum = 0;
        long long maxi = nums[0]; // Initialize with the first element

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];

            if (sum > maxi) {
                maxi = sum;
            }
            
            // If the current sum becomes negative, it's better
            // to start a new subarray from the next element.
            if (sum < 0) {
                sum = 0;
            }
        }
        return maxi;
    }
};
#include <iostream>
#include <vector>
using namespace std;
int main() {
    Solution sol;
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    
    int result = sol.maxSubArray(nums);
    cout << "Maximum subarray sum is: " << result << endl;

    return 0;
}