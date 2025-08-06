#include <bits/stdc++.h>
using namespace std;
int isSorted(int n,vector<int> a){
    for(int i=1 ; i<n ; i++){
        if(a[i]>=a[i-1]){

        }
        else{
            return false;
        }
    }
    return true;
}
int main(){
    vector <int> a = {1, 3 , 2 , 5, 6};
    int n = a.size();
    int ans = isSorted(n, a);
    if(ans){
        cout << "array is sorted" << endl;
    } else{
        cout << "array is not sorted" << endl;
    }
    }
