#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        vector<long long> sur(grid.size()*grid[0].size()),pre(grid.size()*grid[0].size());
        //product mat[i][j] is the product of all except g[i][j]
        //so we prepared 2 partial products:
        //pre: products from (0,0) -> (i,j)
        //which follow the order (0,0),(0,1),...(0,n),(1,0)...
        //pre: products from (n,m) -> (i,j)
        //which follow the order (n,m),(n,m - 1),...(n,0),(n - 1,m)...
        //we use only 1 varible for easy access different rows
        pre[0] = grid[0][0] % 12345;
        for(int i = 1;i < grid.size()*grid[0].size();++i){
            pre[i] = (pre[i - 1] * grid[i / grid[0].size()][i % grid[0].size()])%(12345);
        }
        sur[grid.size()*grid[0].size() - 1] = grid[grid.size() - 1][grid[0].size() - 1] % 12345;
        for(int i = grid.size()*grid[0].size() - 2;i >= 0;--i){
            sur[i] = (sur[i + 1] * grid[i / grid[0].size()][i % grid[0].size()])%(12345);
        }
        vector<vector<int>> out(grid.size() ,vector<int>(grid[0].size() ));
        //2 products which only need 1 pratial product
        //first and the last;
        out[0][0] = sur[1];
        out[grid.size() - 1][grid[0].size() - 1] = pre[grid.size()*grid[0].size() - 1 - 1];
        for(int i = 1;i < grid.size()*grid[0].size() - 1;++i){
            //(0,0) to 
            out[i / grid[0].size()][i % grid[0].size()] = (pre[i - 1]*sur[i + 1])%(12345);
        }
        return out;
        
    }
};
int main(){
    vector<vector<int>> g ={{1,2},{3,4}};
    Solution s;
    s.constructProductMatrix(g);
}