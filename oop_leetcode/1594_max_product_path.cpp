#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        vector<vector<vector<long long>>> sliding_max_product(grid.size(),vector<vector<long long>>(grid[0].size(),{LLONG_MIN,LLONG_MIN}));
        //{first,second} = {high , low}
        sliding_max_product[0][0][0] = grid[0][0];
        //we memo all the biggest and smallest for all position
        for(int j = 1;j < grid[0].size();++j){
            sliding_max_product[0][j][0] = grid[0][j] * sliding_max_product[0][j - 1][0];
        }
        for(int i = 1;i < grid.size();++i){ 
            sliding_max_product[i][0][0] = sliding_max_product[i - 1][0][0] * grid[i][0];
            for(int j = 1;j < grid[0].size();++j){
                vector<long long> products;
                //for all 4 products = max0 * g ,max1 * g,min1 * g,min0 * g;
                //if exist then take in the products array
                if(sliding_max_product[i - 1][j][0] != LLONG_MIN){
                    products.push_back(sliding_max_product[i - 1][j][0] * grid[i][j]);
                }
                if(sliding_max_product[i - 1][j][1] != LLONG_MIN){
                    products.push_back(sliding_max_product[i - 1][j][1] * grid[i][j]);
                }
                if(sliding_max_product[i][j - 1][0] != LLONG_MIN){
                    products.push_back(sliding_max_product[i][j - 1][0] * grid[i][j]);
                }
                if(sliding_max_product[i][j - 1][1] != LLONG_MIN){
                    products.push_back(sliding_max_product[i][j - 1][1] * grid[i][j]);
                }
                //take the max and min
                sliding_max_product[i][j][0] = *max_element(products.begin(),products.end());
                sliding_max_product[i][j][1] = *min_element(products.begin(),products.end());
            }
        }
        //if the max_product does not exist then -1.
        return (sliding_max_product[(grid.size() - 1)][grid[0].size() - 1][0] >= 0)?(int)(sliding_max_product[(grid.size() - 1)][grid[0].size() - 1][0]%((int)1e9 + 7)): -1;
    }
};
int main(){
    vector<vector<int>> g = {{-1,3},{0,4}};
    Solution s;
    cout << s.maxProductPath(g);
}