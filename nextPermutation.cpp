class Solution {
public:
     vector<int> nextPermutation(vector<int>& nums) {
        int ind = -1;
        int n = nums.size();
        for(int i=n-2;i>=0;i--){
            if(nums[i]<nums[i+1]){
                ind = i;
                break;
            }
        }
        if(ind == -1){
            reverse(nums.begin(),nums.end());
            return nums;
        }
        for(int i = n-1; i>ind ;i--){
            if(nums[i]>nums[ind]){
                swap(nums[i],nums[ind]);
                break;
            }
        }
        reverse(nums.begin()+ind+1,nums.end());
        return nums;
    }
};
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> nums = {1, 2, 3};
    
    Solution sol;
    vector<int> result = sol.nextPermutation(nums);
    
    cout << "Next permutation: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
