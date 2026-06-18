#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minOperations(string s) {
        int _0_front_operations = 0;
        int _1_front_operations = 0;
        for(int i = 0;i < s.size() ;++i){
            //f(i) = i % 2 => 101010...
            //f2(i) = !(i % 2) => 010101...
            //there is only 2 way so we chack the operation used of these 2 and take the minimum
            _0_front_operations += ((s[i] - '0') ^ ((i % 2)));
            _1_front_operations += ((s[i] - '0') ^ (!(i % 2)));
        }
        return min(_0_front_operations,_1_front_operations);
    }
};