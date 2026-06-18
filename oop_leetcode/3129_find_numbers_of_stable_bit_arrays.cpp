#include<bits/stdc++.h>
using namespace std;
class Solution {
    struct consecutive_same_bit{
        vector<int> consecutive[2];
        int sum[2];
        consecutive_same_bit(int limit){
            consecutive[0].resize(limit,0);
            consecutive[1].resize(limit,0);
            sum[0] = 0;
            sum[1] = 0;
        }
        void add_possible_arrays(int n,int consecutive_ns,int consecutive_num){
            this->consecutive[consecutive_num][consecutive_ns - 1] = (this->consecutive[consecutive_num][consecutive_ns - 1] + n)%((int)1e9 + 7);
            this->sum[consecutive_num] = (this->sum[consecutive_num] + n)%((int)1e9 + 7);
        }
    };
    
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        //a[i][j][l][k] => number of possible stable bit arrays of i '0's and j '1's with k + 1 consecutive ls (l is 0 or 1);
        //a[i][j][l][k] = a[i][j - 1][l - 1][k];
        //a[i][j][1][1] = sum(a[i][j - 1][0][k])
        //a[i][j][0][1] = sum(a[i - 1][j][1][k])
        //time complexity O(z*o*l) O(n^3)
        //space complexity O(z*o*l) O(n^3)
        vector<vector<consecutive_same_bit>> DP_matrix_i0s_j1s(zero + 1,vector<consecutive_same_bit>(one + 1,consecutive_same_bit(limit)));
        for(int i = 1;i <= min(one,limit); ++i){
            //1,11,111... i '1's and 0 '0's with i consecutive '1's
            DP_matrix_i0s_j1s[0][i].add_possible_arrays(1,i, 1);
        }
        for(int i = 1;i <= min(zero,limit); ++i){
            //0,00,000... i '0's and 0 '1's with i consecutive '0's
            DP_matrix_i0s_j1s[i][0].add_possible_arrays(1,i, 0);
        }
        for(int i = 1;i <= zero;++i){
            for(int j = 1;j <= one;++j){
                //append 1 over 0s, one less '1'
                DP_matrix_i0s_j1s[i][j].add_possible_arrays(DP_matrix_i0s_j1s[i][j - 1].sum[0],1,1);
                //append 0 over 1s, one less '0'
                DP_matrix_i0s_j1s[i][j].add_possible_arrays(DP_matrix_i0s_j1s[i - 1][j].sum[1],1,0);
                for(int k = 2; k <= min(zero,limit);++k){
                    //append 0 over 0s, one less '0'
                    //the first -1 is to search the k - 1 consecutive,the second is the  k - 1 consecutive is stored on k - 1 - 1 on the consecutive[]
                    DP_matrix_i0s_j1s[i][j].add_possible_arrays(DP_matrix_i0s_j1s[i - 1][j].consecutive[0][k - 1 - 1],k,0);
                }
                for(int k = 2; k <= min(one,limit);++k){
                    //append 1 over 1s, one less '1'
                    DP_matrix_i0s_j1s[i][j].add_possible_arrays(DP_matrix_i0s_j1s[i][j - 1].consecutive[1][k - 1 - 1],k,1);
                }
            }
        }
        return (DP_matrix_i0s_j1s[zero][one].sum[0] + DP_matrix_i0s_j1s[zero][one].sum[1])%((int)1e9 + 7);
    }
};
int main(){
    Solution s;
    cout << s.numberOfStableArrays(20,15,75);
}