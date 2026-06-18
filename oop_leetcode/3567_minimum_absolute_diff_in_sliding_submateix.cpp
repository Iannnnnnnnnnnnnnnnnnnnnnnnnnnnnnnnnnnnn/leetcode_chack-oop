#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        vector<vector<int>> out(grid.size() - k + 1,vector<int>(grid[0].size() - k + 1));
        set<int> nums_set;
        for(int i = 0;i < (grid.size() - k + 1);++i){
            for(int j = 0;j < (grid[0].size() - k + 1);++j){
                int smallest_diff = INT_MAX;
                //collecting all number
                for(int subi = 0;subi < k;++subi){
                    for(int subj = 0;subj < k;++subj){
                        nums_set.insert(grid[i + subi][j + subj]);
                    }
                }
                if(nums_set.size() == 1){
                    smallest_diff = 0;
                }
                //we dont have to compare every 2
                //just sort it and
                //a1 a2 a3 ... an if we look any 2 nums, that is not an and an - 1 like ak and ak + 2
                //there is always ak ak + 1 have smaller dis
                for(set<int>::iterator iter = nums_set.begin();iter != prev(nums_set.end());iter++){
                    if(smallest_diff == 0){
                        smallest_diff = 0;
                        break;
                    }
                    //so we look the minimum diff
                    smallest_diff = min(smallest_diff,*next(iter) - *iter);
                }
                nums_set.clear();
                out[i][j] = smallest_diff;
            }
        }
        return out;
    }
};
int main(){
    vector<vector<int>>   g = {{1,-2,3},{2,3,5}};
    Solution s;
    vector<vector<int>> out = s.minAbsDiff(g,2);
}