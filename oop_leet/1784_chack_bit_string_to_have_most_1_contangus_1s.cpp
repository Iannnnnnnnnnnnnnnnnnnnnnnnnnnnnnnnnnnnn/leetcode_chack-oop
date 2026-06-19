#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool checkOnesSegment(string s) {
        //"0" or "1" have < 2 segment of 1s
        if(s.size() == 1)return true;
        unsigned char segment_1s_count = 0;
        for(int i = 1;i < s.size();i++){
            //if there is "10" there is an end of a segment of 1
            //we cant not tolerate "01" after "10";
            if((s[i - 1] == '1') && (s[i] == '0'))segment_1s_count = 1;
            //
            if(segment_1s_count && ((s[i - 1] == '0') && (s[i] == '1')))return false;
        }
        return true;
    }
};