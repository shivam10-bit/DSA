#include<iostream>
#include <vector>
#include <map>
using namespace std;
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int>mpp;
        int n = nums.size();
        for(int i=0;i<n;i++){
            int moreNeeded = target - nums[i];
            if(mpp.find(moreNeeded)!=mpp.end()){
                return {mpp[moreNeeded],i};
            }
            mpp[nums[i]]=i;
        }
        return {};
    }
int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = twoSum(nums, target);
    if (!result.empty()) {
        cout << "Indices of the two numbers that add up to " << target << " are: "
             << result[0] << " and " << result[1] << endl;
    } else {
        cout << "No two numbers add up to " << target << endl;
    }
    return 0;
}