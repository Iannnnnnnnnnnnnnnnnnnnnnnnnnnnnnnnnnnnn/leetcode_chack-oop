#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minPartitions(string n) {
        int max_digit = 0;
        //2531 = 1111 + 1110 + 110 + 100 + 100 so search the max_digit
        //1111
        //1110
        //0110
        //0100
        //0100
        for(string::iterator i = n.begin();i != n.end();i++){
            if((*i - '0') > max_digit){
                max_digit = (*i - '0');
            }
        }
        return max_digit;
    }
};