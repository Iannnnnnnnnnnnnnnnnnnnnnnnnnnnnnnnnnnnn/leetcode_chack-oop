#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.size(),m = str2.size();
        string strout;
        for(int i = n + m - 1 - 1;i >= 0;i--){
            strout.push_back('a');
        }
        vector<unsigned int> strout_possibile_chars(n + m - 1,0xffffffff);
        for(int i = n - 1;i >= 0;i--){
            if(str1[i] != 'T')continue;
            for(int j = 0;j < m;j++){
                strout_possibile_chars[i + j] &= (0x1 << (str2[j] - 'a'));
            }
        }
        //conflict of T and T
        for(int i = m + n - 1 - 1;i >= 0; --i){
            if((strout_possibile_chars[i] & 0x3ffffff) == 0)return string();
            //all is supposed to be 'a'
            strout[i] = __builtin_ffs(strout_possibile_chars[i]) - 1 + 'a';
        }
        for(int i = 0;i < n; i++){

            if(str1[i] != 'F'){
                continue;
            }
            //suppose 'a' would not have problems, if have then use b to fix
            bool problems = true;
            for(int j = 0;j < m;j++){
                if(strout[i + j] != str2[j]){
                    problems = false;
                    break;
                }
            }
            //if there is a problem: see if there is a way to fix it
            if(!problems)continue;
            bool not_locked_found = false;
            for(int j = m - 1;j >= 0;--j){
                if(strout_possibile_chars[i + j] == 0xffffffff){
                    not_locked_found = true;
                    //fix the problem
                    //after fixing the problem the new problem is always on the back of the point fixed
                    //for some strings that if we move left by k, the string match partially of itself
                    //there is only one matching patterns:
                    //if there is a string that have 2 way of matching which have different matching patterns.
                    //one patterns is matched partially by move left k0, the other is one patterns is matched partially by move left k1
                    //think if the string is very long so that we can move left by the least common mutiple of both k0 and k1
                    //the pattern of the string is the same, and that contradict the hypothesis.(have 2 way of matching which have different matching patterns)
                    strout[i + j] = 'b';
                    //and the character is locked
                    strout_possibile_chars[i + j] = 0x2;
                    break;
                }
            }
            if(not_locked_found == false){
                return string();
            }
        }
        return strout;
    }
};
int main(){
    string s1 = "TFFFT";
    string s2 = "bab";
    Solution s;
    cout << s.generateString(s1,s2);
}