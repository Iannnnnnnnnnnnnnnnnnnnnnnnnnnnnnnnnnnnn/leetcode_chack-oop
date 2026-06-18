#include<bits/stdc++.h>
using namespace std;
class Solution {
    char char_bit_not(char c){
        if(c == '0')return '1';
        return '0';
    }
public:
    char findKthBit(int n, int k) {
        if(n <= 1){
            //s1 = "0"
            return '0';
        }
        if(k == (1 << (n - 1))){
            //for all n that s(n,2^(n-1)) == "1"
            return '1';
        }else if(k > (1 << (n - 1))){
            //because the bits are inverted and reversed, so it is corrasponded onto the last bit string
            //s(n,k) = not(s(n-1,2^n - k)) if k > 2^(n - 1)
            return char_bit_not(findKthBit(n - 1, (1 << n) - k));
        }else{
            //this is directily onto
            //s(n,k) = not(s(n-1,k)) if k < 2^(n - 1)
            return findKthBit(n - 1, k);
        }
    }
};