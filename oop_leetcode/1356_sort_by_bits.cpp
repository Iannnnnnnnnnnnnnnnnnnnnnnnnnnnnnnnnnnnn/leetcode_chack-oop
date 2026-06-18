#include<bits/stdc++.h>
using namespace std;
class Solution {
    static bool cmp(const int a,const int b){
        //__builtin_popcount count set bit in an interger
        if(__builtin_popcount(a) == __builtin_popcount(b)){
            return a < b;
        }
        return __builtin_popcount(a) < __builtin_popcount(b);
    }
public:
    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(),arr.end(),cmp);
        return arr;
    }
};