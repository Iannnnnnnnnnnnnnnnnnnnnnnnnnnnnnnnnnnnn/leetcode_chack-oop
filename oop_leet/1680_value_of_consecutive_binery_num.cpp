#include<bits/stdc++.h>
using namespace std;
class Solution {
    int bits_used(int n){
        int i = 1,count = 0;
        while (i <= n){
            i <<= 1;
            ++count;
        }
        return count;
    }
public:
    //maxinum of n is 10^5;
    int concatenatedBinary(int n) {
        int res = 0;
        unsigned long long bit_move = 1;
        for(int i = n;i > 0;--i){
            res = (res + (int)((i*bit_move)%((int)1e9 + 7)))%((int)1e9 + 7);
            bit_move = ((bit_move << bits_used(i))%((unsigned long long)1e9 + 7ull));
        }
        return res;
    }
};
int main(){
    Solution s;
    cout<< s.concatenatedBinary(42);
}