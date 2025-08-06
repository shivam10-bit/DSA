class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> map;
        for (int i = 0; i < nums.size(); ++i) {
            int need = target - nums[i];
            if (map.count(need)) {
                return { map[need], i };
            }
            map[nums[i]] = i;
        }
        return {};
    }
};
#include <iostream>
#include <vector>   
#include <unordered_map>
#include <iostream>
    
using namespace std;
int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    Solution sol;
    vector<int> result = sol.twoSum(nums, target);
    
    if (!result.empty()) {
        cout << "Indices of the two numbers that add up to " << target << " are: "
             << result[0] << " and " << result[1] << endl;
    } else {
        cout << "No two numbers add up to " << target << endl;
    }
    
    return 0;
}