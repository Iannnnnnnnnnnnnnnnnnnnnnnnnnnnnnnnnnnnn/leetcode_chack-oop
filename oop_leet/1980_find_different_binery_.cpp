#include<bits/stdc++.h>
using namespace std;
class Solution {
    //turn binery string into Uint16
    unsigned short binery_into_Uint16(string s){
        short res,i = (unsigned short)(s.size());
        //for i from n - 1to 0, add each bit into the number
        while (i--){
            res += ((s[i] - '0') << (s.size() - i - 1));
            
        }
        return res;
    }
    string Uint16_into_binery(unsigned short n,int length){
        string res;
        //(most significant bit)11100 -> last char of s.
        //for i from n - 1 to 0, append each bit into a string
        for(int i = (length - 1);i >= 0;--i){
            if((n & (1 << i)) != 0){
                res.push_back('1');
            }else{
                res.push_back('0');
            }
        }
        return res;
    }
public:
    string findDifferentBinaryString(vector<string>& nums) {
        vector<unsigned short> ns(nums.size(),0);
        //find any unique binery string of length n 
        //because n <= 16 so unsigned short (Uint16) would fit
        for(int i = 0;i < nums.size();i++){
            ns[i] = binery_into_Uint16(nums[i]);
        }
        //sort numbers
        sort(ns.begin(),ns.end());
        //try 0 first
        if(ns[0] > 0)return Uint16_into_binery(0,nums.size());
        for(int i = 0;i < (nums.size() - 1);++i){
            //try each ns[i] + 1 ,because numbers is sorted so if the ns[i] + 1 != ns[i] there is a gap to fill
            if((ns[i] + 1) != ns[i + 1])return Uint16_into_binery(ns[i] + 1,nums.size());
        }
        //if none in the middle, must in the end
        return Uint16_into_binery(ns[nums.size() - 1] + 1,nums.size());        
    }
};
int main(){
    Solution s;
    vector<string> nums = {"00","10"};
    cout << s.findDifferentBinaryString(nums);
}