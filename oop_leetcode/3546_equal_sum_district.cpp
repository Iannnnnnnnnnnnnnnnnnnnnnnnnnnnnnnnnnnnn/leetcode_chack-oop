#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        vector<vector<long long>> sum(grid.size() + 1,vector<long long>(grid[0].size() + 1,0));
        //a array of sums of the interval (0,0) to (i,j)
        for(int i = 1;i <= grid.size();++i){
            for(int j = 1;j <= grid[0].size();++j){
                sum[i][j] = sum[i - 1][j] + grid[i - 1][j - 1] + sum[i][j - 1] - sum[i - 1][j - 1];
            }
        }
        //if ahe sum of all is odd then there is no way to partition that
        if(sum.back().back() & 1)return false;
        for(int i = 1;i < grid[0].size();++i){
            //if one partition is the half of all, which means other half is the same
            //vertical ones
            if(sum[grid.size()][i] == (sum.back().back() >> 1)){
                return true;
            }
        }
        for(int i = 1;i < grid.size();++i){
            //horizontial ones
            if(sum[i][grid[0].size()] == (sum.back().back() >> 1)){
                return true;
            }
        }
        return false;
    }
};
int main(){
    vector<vector<int>> g = {{1,4},{2,3}};
    Solution s;
    s.canPartitionGrid(g);
}