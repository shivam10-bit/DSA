
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> pascal(numRows);

        for (int i = 0; i < numRows; i++) {
            pascal[i].resize(i + 1);   // each row has i+1 elements
            pascal[i][0] = pascal[i][i] = 1;  // first and last elements are 1

            for (int j = 1; j < i; j++) {
                pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
            }
        }

        return pascal;
    }
};
        
#include <iostream>
   
#include <iostream>
#include <vector>
using namespace std;

int main() {
    Solution sol;
    int numRows = 5; // Example number of rows
    vector<vector<int>> pascalTriangle = sol.generate(numRows);

    cout << "Pascal's Triangle:" << endl;
    for (const auto& row : pascalTriangle) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}