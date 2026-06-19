#include<bits/stdc++.h>
using namespace std;
class Solution {
    class DP_number_of_stableArrays_i1s_j0s{
        //have 
        vector<vector<vector<int>>> num_of_array;
        int limit;
    public:
        DP_number_of_stableArrays_i1s_j0s(int maxZeros,int maxOnes,int limit):num_of_array(vector<vector<vector<int>>>(maxOnes + 1,vector<vector<int>>(maxZeros + 1,{0,0,0,0}))){
            //l ends with l and l is the first consecutive bit
            //1,0
            num_of_array[1][0][1 | 2] = 1;
            num_of_array[0][1][0 | 2] = 1;
            //if limit is larger than number of 1s then the method that only use limit would cause out of index 
            for(int i = 2; i <= min(maxOnes,limit); ++i){
                //1,11,111,...last digit is always 1
                num_of_array[i][0][1] = 1;
            }
            for(int i = 2; i <= min(maxZeros,limit); ++i){
                //0,00,000,...last digit is always 0
                num_of_array[0][i][0] = 1;
            }
            this->limit = limit;
        }
        //i , j must > 1
        void set_number_of_stableArrays_pos(int i,int j){
            // j - 1 > 0
            //add 0 over 1s, one less 0
            //and the added digit is the first;
            //the first bit of a in this->num_of_array[i][j][a] is the last digit
            //the second bit of a in this->num_of_array[i][j][a] is:
            //1: the first
            //0: not
            //and that is how  | 2 comes
            this->num_of_array[i][j][0 | 2] = ((this->num_of_array[i][j][0 | 2] + this->num_of_array[i][j - 1][1])%((int)1e9 + 7) + this->num_of_array[i][j - 1][1 | 2])%((int)1e9 + 7);
            //add 0 over 0s, one less 0 
            //and the added digit is not the first;
            this->num_of_array[i][j][0] = ((this->num_of_array[i][j][0] + this->num_of_array[i][j - 1][0])%((int)1e9 + 7) + this->num_of_array[i][j - 1][0 | 2])%((int)1e9 + 7);
            if(j > limit){// j - limit > 0
                //remove those that would be unstable
                //so we need to chack those is the first
                //x0 -> x00 -> x000(unstable for limit = 2)
                this->num_of_array[i][j][0] = (this->num_of_array[i][j][0] + (((int)1e9 + 7) - this->num_of_array[i][j - limit][0 | 2]))%((int)1e9 + 7);
            }
            // j - 1 > 0
            //add 1 over 0s, one less 1
            //and the added digit is the first;
            this->num_of_array[i][j][1 | 2] = ((this->num_of_array[i][j][1 | 2] + this->num_of_array[i - 1][j][0])%((int)1e9 + 7) + this->num_of_array[i - 1][j][0 | 2])%((int)1e9 + 7);
            //add 1 over 1s, one less 1
            //and the added digit is not the first;
            this->num_of_array[i][j][1] = ((this->num_of_array[i][j][1] + this->num_of_array[i - 1][j][1])%((int)1e9 + 7) + this->num_of_array[i - 1][j][1 | 2])%((int)1e9 + 7);
            if(i > limit){// j - limit > 0
                //remove those that would be unstable
                //so we need to chack those is the first
                this->num_of_array[i][j][1] = (this->num_of_array[i][j][1] + (((int)1e9 + 7) - this->num_of_array[i - limit][j][1 | 2]))%((int)1e9 + 7);
            }
        }
        int get_number_of_stableArrays_pos(int i,int j){
            return ((this->num_of_array[i][j][0] + this->num_of_array[i][j][1])%((int)1e9 + 7) + (this->num_of_array[i][j][2] + this->num_of_array[i][j][3])%((int)1e9 + 7))%((int)1e9 + 7);
        }
    };
    
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        //a[i][j][l&0x1 + m * 2] => number of possible stable bit arrays of i '1's and j '0's that the last digit is l,l is 0 or 1 and m is if the digit is the first one
        //add 0 over 1s, one less 0
        //add 0 over 0s, one less 0
        //a[i][j][0] = (a[i][j - 1][1] + (a[i][j - 1][0] - a[i][j - limit][0](these would bo unstable)))
        //add 0 over 1s, one less 0
        //add 0 over 0s, one less 0
        //time complexity O(z*o*2) O(n^2)
        //space complexity O(z*o*2) O(n^2)
        DP_number_of_stableArrays_i1s_j0s DP(zero,one,limit);
        for(int i = 1; i <= one;++i){
            for(int j = 1;j <= zero;++j){
                DP.set_number_of_stableArrays_pos(i,j);
            }
        }
        return DP.get_number_of_stableArrays_pos(one,zero);
        
    }
};
int main(){
    Solution s;
    cout << s.numberOfStableArrays(1,4,2);
}