#include<bits/stdc++.h>
using namespace std;
class Solution {
    class frequency_map_string{
        vector<int> frequency_map;
    public:
        frequency_map_string(string & s,int origin,int fre){
            frequency_map = vector<int>(26,0);
            for(int i = origin;i < s.size();i += fre){
                frequency_map[s[i] - 'a']++;
            }
        }
        bool operator==(const frequency_map_string & f1){
            for(int i = 0;i < 26;++i){
                if(this->frequency_map[i] != f1.frequency_map[i]){
                    return false;
                }
            }
            return true;
        }
    };
public:
    bool checkStrings(string s1, string s2) {
        //see that if the frequency of both odd and even indices of both strings match
        frequency_map_string fs1[2] = {frequency_map_string(s1,0,2),frequency_map_string(s1,1,2)};
        frequency_map_string fs2[2] = {frequency_map_string(s2,0,2),frequency_map_string(s2,1,2)};
        if((fs1[0] == fs2[0]) && (fs1[1] == fs2[1])){
            return true;
        }
        return false;
    }
};