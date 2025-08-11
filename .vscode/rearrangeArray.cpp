class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n,0);
        int posIndex = 0,negIndex = 1;
        for(int i=0;i<n;i++){
            if(nums[i]<0){
                ans[negIndex]=nums[i];
                negIndex+=2;
            }
            else{
                ans[posIndex]=nums[i];
                posIndex+=2;
            }
        }
        return ans;
    }
};
#include <iostream>
#include <vector>
using namespace std;
int main() {
    Solution sol;
    vector<int> nums = {3, -2, 1, -5, 4};
    
    vector<int> result = sol.rearrangeArray(nums);
    
    cout << "Rearranged array: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
