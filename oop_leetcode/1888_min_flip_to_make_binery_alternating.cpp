#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minFlips(string s) {
        if(s.size() == 1)return 0;
        int flip_needed[2] = {0,0}; // flips requied for both 101 010 for i > 1
        int minimum_flips = INT_MAX;
        //[0] = flip needed to get 010...
        //[1] = flip needed to get 101...
        for(int i = 0;i < s.size(); ++i){
            flip_needed[0] += ((i % 2)^(s[i] - '0'));
            flip_needed[1] += ((!(i % 2))^(s[i] - '0'));
        }
        minimum_flips = min({flip_needed[0] ,flip_needed[1] , minimum_flips});
        for(int i = 0;i < (s.size() - 1);++i){
            //what are going to remove is always the front
            flip_needed[0] -= ((0)^(s[i] - '0'));
            flip_needed[1] -= ((1)^(s[i] - '0'));
            //substute the flip needed for index i, because this is moving to the back
            //and get the number of flips for j > 1 of s[j]
            //flips[0](101...) -> flips[0](01...)
            //flips[0](010...) -> flips[0](10...)
            //flips[1](101...) = flips[1](10...) + flip needed for index 0;
            swap(flip_needed[0],flip_needed[1]);
            //what are going to add is always the end
            flip_needed[0] += (((s.size() - 1) % 2)^(s[i] - '0'));
            flip_needed[1] += ((!((s.size() - 1) % 2))^(s[i] - '0'));
            minimum_flips = min({flip_needed[0] ,flip_needed[1] , minimum_flips});

        }
        return minimum_flips;
    }
};