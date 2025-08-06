#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // XOR-based missing number finder in range [0..N]
    int missingNumber(const vector<int>& a) {
        int n = a.size();
        int xor_arr = 0, xor_full = 0;
        for(int v : a) xor_arr ^= v;
        for(int i = 0; i <= n; i++) xor_full ^= i;
        return xor_full ^ xor_arr;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N; // input total count including missing (e.g., 5 means 0..5 with one missing)
    vector<int> a(N);
    for(int i = 0; i < N; i++) cin >> a[i];

    int result = Solution().missingNumber(a);
    cout << result << "\n";
    return 0;
}
