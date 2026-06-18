#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        vector<int> row_positions_of_first_1s(mat.size(),-1), column_positions_of_first_1s(mat[0].size(),-1);
        for(int i = 0;i < mat.size();++i){
            for(int j = 0;j < mat[i].size();++j){
                if(mat[i][j] != 0){
                    if(row_positions_of_first_1s[i] != -1){
                        row_positions_of_first_1s[i] = -1;
                        break;
                    }
                    row_positions_of_first_1s[i] = j;
                }
            }
        }
        for(int j = 0;j < mat[0].size();++j){
            for(int i = 0;i < mat.size();++i){
                if(mat[i][j] != 0){
                    if(column_positions_of_first_1s[j] != -1){
                        column_positions_of_first_1s[j] = -1;
                        break;
                    }
                    column_positions_of_first_1s[j] = i;
                }
            }
        }
        int count = 0;
        if(mat.size() > mat[0].size()){
            for(int i = 0;i < mat.size();i++){
                if(row_positions_of_first_1s[i] == -1)continue;
                if(column_positions_of_first_1s[row_positions_of_first_1s[i]] == i)count++;
            }
        }else{
            for(int j = 0;j < mat[0].size();j++){
                if(column_positions_of_first_1s[j] == -1)continue;
                if(row_positions_of_first_1s[column_positions_of_first_1s[j]] == j)count++;
            }
        }
        return count;
    }
};
int main(){
    Solution s;
    vector<vector<int>> mat = {{1,0,0},{0,0,1},{1,0,0}};
    cout<< s.numSpecial(mat);
}