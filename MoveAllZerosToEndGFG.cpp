#include <iostream>
#include <vector>

void pushZerosToEnd(std::vector<int>& arr) {
    int n = arr.size();
    int count = 0; // Position to place the next non-zero element

    // Traverse the array
    for (int i = 0; i < n; ++i) {
        if (arr[i] != 0) {
            // Swap only if current index is not the same as count
            if (i != count) {
                std::swap(arr[i], arr[count]);
            }
            ++count;
        }
    }
}

int main() {
    std::vector<int> arr = {1, 0, 2, 0, 3, 0, 4, 5};
    pushZerosToEnd(arr);

    std::cout << "Array after moving zeros to the end:\n";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
