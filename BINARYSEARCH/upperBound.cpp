#include<stdio.h>
#include<vector>
using namespace std;
int upperBound(vector<int>arr , int n , int x){
    int low = 0 , high = n-1;
    int n = arr.size();
    int ans= n;
    while(low<high){
        int mid = (low+high)/2;
        if(arr[mid]>x){
            ans = mid;
            high = mid - 1;
        }
        else{
            low = mid+1;
        }
    }
    
}