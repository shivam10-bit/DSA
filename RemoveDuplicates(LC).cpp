#include <iostream>
#include <vector>

// Function to remove duplicates from a sorted array
int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;

    int i = 0;
    for (int j = 1; j < nums.size(); ++j) {
        if (nums[i] != nums[j]) {
            ++i;
            nums[i] = nums[j];
        }
    }
    return i + 1;
}

int main() {
    std::vector<int> nums = {1, 1, 2, 2, 3, 4, 4, 5};

    int newLength = removeDuplicates(nums);

    std::cout << "Array after removing duplicates: ";
    for (int i = 0; i < newLength; ++i) {
        std::cout << nums[i] << " ";
    }
    std::cout << "\nNew length: " << newLength << std::endl;

    return 0;
}
