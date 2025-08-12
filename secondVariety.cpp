vector<int> alternateNumbers(vector<int> &a){
    vector <int> pos,neg;
    int n=a.size();
    for(int i=0;i<n;i++){
        if(a[i]>=0){
            pos.push_back(a[i]);
        }
        else{
            neg.push_back(a[i]);
        }
    }
    if(pos.size()>neg.size()){
        int i=0,j=0;
        vector<int> ans;
        while(i<pos.size() && j<neg.size()){
            ans.push_back(pos[i++]);
            ans.push_back(neg[j++]);
        }
        while(i<pos.size()){
            ans.push_back(pos[i++]);
        }
        return ans;
    }
    else{
        int i=0,j=0;
        vector<int> ans;
        while(i<pos.size() && j<neg.size()){
            ans.push_back(neg[j++]);
            ans.push_back(pos[i++]);
        }
        while(j<neg.size()){
            ans.push_back(neg[j++]);
        }
        return ans;
    }
}
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> nums = {3, -2, 1, -5, 4};
    
    vector<int> result = alternateNumbers(nums);
    
    cout << "Rearranged array: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
