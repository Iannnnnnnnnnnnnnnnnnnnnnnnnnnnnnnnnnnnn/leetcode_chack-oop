#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        //sliding windows
        vector<int> sum_x(grid[0].size(),0);
        int prev_recounted_rect_sumX = 0;
        vector<int> sum_y(grid[0].size(),0);
        int prev_recounted_rect_sumY = 0;
        int count = 0;
        for(int i = 0;i < grid.size();++i){
            
            prev_recounted_rect_sumX = sum_x[0];
            sum_x[0] = sum_x[0] + ((!(grid[i][0] & 0x2) && !(grid[i][0] & 0x1)));
            prev_recounted_rect_sumY = sum_y[0];
            sum_y[0] = sum_y[0] + ((!(grid[i][0] & 0x2)) && (grid[i][0] & 0x1));
            
            if(((sum_x[0] ^ sum_y[0]) == 0) && (sum_x[0] != 0)){
                count++;
            }
            for(int j = 1;j < grid[0].size();++j){
                int temp = 0;
                temp = sum_x[j] + ((!(grid[i][j] & 0x2)) &&(!(grid[i][j] & 0x1))) + sum_x[j - 1] - prev_recounted_rect_sumX;
                prev_recounted_rect_sumX = sum_x[j];
                sum_x[j] = temp; 
                temp = sum_y[j] + ((!(grid[i][j] & 0x2)) && (grid[i][j] & 0x1)) + sum_y[j - 1] - prev_recounted_rect_sumY;
                prev_recounted_rect_sumY = sum_y[j];
                sum_y[j] = temp;
                
                if(((sum_x[j] ^ sum_y[j]) == 0) && (sum_x[j] != 0)){
                    count++;
                }
            }
        }
        return count;
    }
};
int main(){
    //printf("%x %x %x",'X','Y','.');
    vector<vector<char>> v = {{'X','Y','.'},{'Y','.','.'}};
    Solution s;
    cout<< s.numberOfSubmatrices(v);

}