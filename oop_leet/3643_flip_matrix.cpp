#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        for(int i = x; i < (x + (k >> 1));++i){
            //just swap 
            for(int j = y; j < (y+k);++j){
                swap(grid[i][j],grid[(x << 1) + k - i - 1][j]);
            }
        }
        return grid;
    }
};