#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int linearSearch(int n,int num,vector<int>& arr, int target) {
        for( int i=0 ; i<n ; i++){
            if(arr[i]=num){
                return i;
            }
        }
        return -1;
    }
};
