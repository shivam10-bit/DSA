class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        
        long long sum = 0;
        long long maxi = nums[0]; 

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];

            if (sum > maxi) {
                maxi = sum;
            }
            
      
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
