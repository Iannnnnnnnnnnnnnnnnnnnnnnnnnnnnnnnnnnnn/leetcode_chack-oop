#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        for(int i = 0;i < mat.size();++i){
            for(int j = 0;j < mat[0].size();++j){
                //if i is even then only move k (right)
                //if i is odd then only move -k = (n - 1) mod n = k(n - 1) mod n
                //so the n - 2 is there
                if(mat[i][j] != mat[i][(j + (k * (i & 1) * (mat[0].size() - 2)) + k)%(mat[0].size())])return false;
            }
        }
        return true;
    }
};