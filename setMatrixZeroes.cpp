//better
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();          // number of rows
        int m = matrix[0].size();       // number of columns

        vector<int> row(n, 0);          // initialize all to 0
        vector<int> col(m, 0);

        // Step 1: Mark rows and columns that need to be zeroed
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }

        // Step 2: Set cells to zero if they are in marked row or column
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (row[i] || col[j]) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<vector<int>> matrix = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };

    Solution sol;
    sol.setZeroes(matrix);

    cout << "Modified matrix:" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}