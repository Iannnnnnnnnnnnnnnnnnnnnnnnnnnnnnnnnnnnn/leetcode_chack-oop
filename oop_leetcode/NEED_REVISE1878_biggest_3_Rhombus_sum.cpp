#include<bits/stdc++.h>
using namespace std;
class Solution {
    struct diagonal_line_sum{
        //visualize
        //   /(right-upper)
        //000
        //000
        //000
        //   \(right lower)
        //ru[i][j] = sum(grid[i + 1][j - 1] + grid[i + 2][j - 2] +...+ grid[i0][j0]) (i0 or j0 = 0 or )
        //rl[i][j] = sum(grid[i - 1][j - 1] + grid[i - 1][j - 2] +...+ grid[i0][j0]) (i0 or j0 = 0)
        vector<vector<int>> right_upper_sum,right_lower_sum;
        diagonal_line_sum(vector<vector<int>>& grid):
            right_upper_sum(vector<vector<int>>(grid.size() + 2,vector<int>(grid[0].size() + 1,0))),
            right_lower_sum(vector<vector<int>>(grid.size() + 2,vector<int>(grid[0].size() + 1,0)))
        {
            for(int j = 1; j <= grid[0].size(); ++j){
                for(int i = 1;i <= grid.size();++i){
                    //first + then =
                    right_upper_sum[i][j] = right_upper_sum[i + 1][j - 1] + grid[i - 1][j - 1];
                    right_lower_sum[i][j] = right_lower_sum[i - 1][j - 1] + grid[i - 1][j - 1];
                }
            }    
        }
        //for a squere (i0,j0) (i1,j1) |i1 - i0| = s is odd
        //a diagonal squere ABDC is the shape that has points: A(i1 - s,j1 - s/2),B(i1 - s/2,j1), C(i1 - s/2,j1 - s), D(i1, j1 - s/2)
        //these four point
        //please chack the margin first (i0,j0 >= 0 ) to avoid errors
        int get_diagonal_squere_sum(int side_length,int i1,int j1){
            if(side_length == 1){
                 return right_lower_sum[i1][j1] - right_lower_sum[i1 - 1][j1 - 1];
            }
            int half_sideL = side_length >> 1;
            return  right_lower_sum[i1 - half_sideL][j1] - right_lower_sum[i1 - side_length/*(side_length - 1 + 1)*/][j1 - half_sideL - 1] + //side  A -> B
                    right_lower_sum[i1][j1 - half_sideL] - right_lower_sum[i1 - half_sideL - 1][j1 - side_length/*(side_length - 1 + 1)*/] +  //side  C -> D
                    right_upper_sum[i1 - side_length + 1 + 1][j1 - half_sideL - 1] - right_upper_sum[i1 - half_sideL][j1 - side_length + 1] +  //side  C -> A with out the value of position A ,C
                    right_upper_sum[i1 - half_sideL + 1][j1 - 1] - right_upper_sum[i1][j1 - half_sideL];  //side  D -> B with out the value of position D ,B


        }
    };
    
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        diagonal_line_sum DLS(grid);
        vector<int> out;
        set<int> values;
        //time complexity: O(m*n(m+n))
        for(int k = 0;k < min(grid.size(),grid[0].size());k += 2){
            for(int i = k;i < grid.size();++i){
                for(int j = k;j < grid[0].size();++j){
                    int grid_sum = DLS.get_diagonal_squere_sum(k + 1,i + 1,j + 1);
                    if((values.size() <= 3) || ((*values.begin()) < grid_sum)){
                        values.insert(grid_sum);
                        if(values.size() > 3)values.erase(values.begin());
                    }
                }
            }
        }
        for(auto it = values.rbegin();it != values.rend(); it++){
            out.push_back(*it);
        }
        return out;
    }
};
int main(){
    //vector<vector<int>> grid = {{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int>> grid = {{20,17,9,13,5,2,9,1,5},{14,9,9,9,16,18,3,4,12},{18,15,10,20,19,20,15,12,11},{19,16,19,18,8,13,15,14,11},{4,19,5,2,19,17,7,2,2}};
    Solution s;
    vector<int> res = s.getBiggestThree(grid);
    for(int i : res){
        cout<< i << ' ';
    }
}