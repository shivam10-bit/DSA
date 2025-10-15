#include<stdio.h>
#include<vector>
using namespace std;
int lowerBound(vector<int>& arr, int target) {
    int n = arr.size();
    int low = 0, high = n; // Notice high is n, not n-1
    while (low < high) { // Use < instead of <=
        int mid = low + (high - low) / 2; // To prevent overflow
        if (arr[mid] < target) {
            low = mid + 1; // Move right if mid element is less than target
        } else {
            high = mid; // Move left otherwise
        }
    }
    return low; // or high, both are same here
}