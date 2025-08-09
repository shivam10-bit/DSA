class Solution {
public:
    int majorityElement(vector<int> v) {
        int cnt = 0;
        int el = -1; // Initialize 'el' to a default value

        // Step 1: Find the candidate for the majority element
        for (int i = 0; i < v.size(); i++) {
            if (cnt == 0) {
                cnt = 1;
                el = v[i];
            } else if (v[i] == el) {
                cnt++;
            } else {
                cnt--;
            }
        }

        // Step 2: Verify if the candidate is the majority element
        int cnt1 = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == el) {
                cnt1++;
            }
        }

        if (cnt1 > (v.size() / 2)) {
            return el;
        }

        // If no majority element exists, return -1 (or handle as per problem spec)
        return -1;
    }
};
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> nums = {3, 2, 3};
    
    Solution sol;
    int majority = sol.majorityElement(nums);
    
    if (majority != -1) {
        cout << "Majority element: " << majority << endl;
    } else {
        cout << "No majority element found." << endl;
    }
    
    return 0;
}