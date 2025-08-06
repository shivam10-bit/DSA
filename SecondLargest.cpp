#include <iostream>
#include <vector>
using namespace std;

int sLargest(vector<int>& a, int n) {
    int largest = a[0];
    int slargest = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] > largest) {
            slargest = largest;
            largest = a[i];
        } else if (a[i] < largest && a[i] > slargest) {
            slargest = a[i];
        }
    }
    return slargest;    
}

vector<int> getSecondOrderElements(int n, vector<int> a) {
    int slargest = sLargest(a, n);
    return {slargest};
}

int main() {
    vector<int> a = {10, 20, 4, 45, 99};
    vector<int> result = getSecondOrderElements(a.size(), a);
    cout << "Second largest element: " << result[0] << endl;
    return 0;
}
