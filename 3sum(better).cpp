// in this case time complexity is exceeded 
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();             // Initialize n properly
        set<vector<int>> st;
        for (int i = 0; i < n; i++) {
            unordered_set<int> hashset;
            for (int j = i + 1; j < n; j++) {
                int third = -(nums[i] + nums[j]);
                if (hashset.count(third)) {
                    vector<int> temp{nums[i], nums[j], third};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
                hashset.insert(nums[j]);
            }
        }
        vector<vector<int>> ans(st.begin(), st.end()); // Build result **after** loop
        return ans;
    }
};
