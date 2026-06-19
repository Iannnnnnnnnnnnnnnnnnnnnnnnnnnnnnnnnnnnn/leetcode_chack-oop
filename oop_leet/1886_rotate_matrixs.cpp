#include<bits/stdc++.h>
using namespace std;
class Solution {
    int get_rotate_num(int i,int j,int k,int n,const vector<vector<int>>& mat){
        //just choose
        int out;
        switch (k)
        {
            case 0:
                out = mat[i][j];
                break;
            case 1:
                out = mat[n - j - 1][i];
                break;
            case 2:
                out = mat[n - i - 1][n - j - 1];
                break;
            case 3:
                out = mat[j][n - i - 1];
                break;
            default:
                out = -1;
                break;
        }
        return out;
    }
    bool rotate_right(vector<vector<int>>& mat, vector<vector<int>>& target,int k,int n){
        //chack if 1 dir are right
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(target[i][j] != get_rotate_num(i,j,k,n,mat))return false;
            }
        }
        return true;
    }
    
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        for(int k = 0; k < 4;++k){
            if(rotate_right(mat,target,k,mat.size())){
                return true;
            }
        }
        return false;
    }
};