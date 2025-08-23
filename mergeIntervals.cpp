#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        // Step 1: Sort intervals by start time
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;
        merged.push_back(intervals[0]);

        // Step 2: Merge overlapping intervals
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= merged.back()[1]) {
                // Overlapping → merge by updating the end
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                // No overlap → push new interval
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }
};



#include <iostream>
#include <vector>
using namespace std;
int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> result = sol.merge(intervals);

    cout << "Merged Intervals: ";
    for (const auto& interval : result) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;

    return 0;
}
