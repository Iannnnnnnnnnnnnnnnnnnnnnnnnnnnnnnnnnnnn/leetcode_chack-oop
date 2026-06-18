#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int bitwiseComplement(int n) {
        if(n == 0)return 1;
        //__builtin_clz(unsigned int) returns the number of leading zeros
        //so 0b111111..... >> __builtin_clz(n) returns the amount of 1s that we need
        //and (n) ^ (~n) = 1111....
        //~n = (n) ^ 11111....
        return (int)((((unsigned int)0xffffffff) >> __builtin_clz((unsigned int)n)) ^ ((unsigned int)n));
    }
    

};