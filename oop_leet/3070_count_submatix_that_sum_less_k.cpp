#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        //the memory complexity O(n)
        //can be further reduced into O(1) with just 4 numbers
        //row_sum[i][j]
        //row_sum[i][j - 1]
        //row_sum[i - 1][j]
        //row_sum[i - 1][j - 1]
        vector<vector<int>> row_sum(2,vector<int>(grid[0].size(),0));
        int count = 0;
        for(int i = 0;i < grid.size();++i){
            row_sum[i & 1][0] = row_sum[!(i & 1)][0] + grid[i][0];
            //because its a sum of a rectangle area
            //the area from (0,0) to (i,j) is
            //(0,0) to (i - 1,j) + 0,0) to (i - 1,j) - (0,0) to (i - 1,j - 1) + the value if position (i,j)
            count += (row_sum[i & 1][0] <= k);
            for(int j = 1;j < grid[i].size();++j){
                row_sum[i & 1][j] = row_sum[!(i & 1)][j] + row_sum[i & 1][j - 1] + grid[i][j] - row_sum[!(i & 1)][j - 1];
                count += (row_sum[i & 1][j] <= k);
            }
        }
        return count;
    }
    
};
int main(){
    Solution s;
    vector<vector<int>> m = {{7,2,9},{1,5,0},{2,6,6}};
    cout << s.countSubmatrices(m,20);
}