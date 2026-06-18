#include<bits/stdc++.h>
using namespace std;
class Solution {
   struct _interger_interval{
        int i_interval[2];
        int j_interval[2];
        _interger_interval(int i,int j){
            i_interval[0] = i;  
            i_interval[1] = i;
            j_interval[0] = j;
            j_interval[1] = j;
        }
        void insert_new_num_pos(int i,int j){
            i_interval[0] = min(i_interval[0],i);
            i_interval[1] = max(i_interval[1],i);
            j_interval[0] = min(j_interval[0],j);
            j_interval[1] = max(j_interval[1],j);
        }
   };
   bool chack_horizontal(vector<vector<int>>& grid,map<long long,_interger_interval>& map_integer,vector<vector<long long>>& map_rectsum){
        long long diff = 0;
        long long upper_sum,lower_sum;
        map<long long,_interger_interval>::iterator iter;
        for(int i = 0;i < grid.size() - 1;++i){
            upper_sum = map_rectsum[i + 1].back();
            lower_sum = map_rectsum.back().back() - map_rectsum[i + 1].back();
            if(upper_sum == lower_sum){
                return true;
            }else if(upper_sum > lower_sum){
                diff = (upper_sum - lower_sum);
                iter = map_integer.find(diff);
                //chack the corners:
                //(0,0)
                //(i,0)
                //(i,b)
                //(0,b)
                if((grid[0][0] == diff) || (grid[0].back() == diff) || (grid[i].back() == diff) || (grid[i][0] == diff))return true;
                else if((i == 0) || (grid[0].size() == 1))continue;
                if(iter == map_integer.end())continue;
                if((*iter).second.i_interval[0] <= (i))return true;
            }else{              //upper_sum < lower_sum
                diff = lower_sum - upper_sum;
                iter = map_integer.find(diff);
                //chack the corners:
                //(b,b)
                //(i + 1,b)
                //(b,0)
                //(i + 1,0)
                if((grid.back()[0] == diff) || (grid.back().back() == diff) || (grid[i + 1].back() == diff) || (grid[i + 1][0] == diff))return true;
                else if((i == (grid.size() - 2)) || (grid[0].size() == 1))continue;
                if(iter == map_integer.end())continue;
                if((*iter).second.i_interval[1] > (i))return true;
            }
        }
        return false;
   }
   bool chack_vertical(vector<vector<int>>& grid,map<long long,_interger_interval>& map_integer,vector<vector<long long>>& map_rectsum){
        long long diff = 0;
        long long left_sum,right_sum;
        map<long long,_interger_interval>::iterator iter;
        for(int j = 0;j < grid[0].size() - 1;++j){
            left_sum = map_rectsum.back()[j + 1];
            right_sum = map_rectsum.back().back() - map_rectsum.back()[j + 1];
            if(left_sum == right_sum){
                return true;
            }else if(left_sum > right_sum){
                diff = (left_sum - right_sum);
                iter = map_integer.find(diff);
                //chack the corners:
                //(0,0)
                //(0,j)
                //(b,j)
                //(b,0)
                if((grid[0][0] == diff) || (grid.back()[0] == diff) || (grid[0][j] == diff) || (grid.back()[j] == diff))return true;
                else if((j == 0) || (grid.size() == 1))continue;
                if(iter == map_integer.end())continue;
                if((*iter).second.j_interval[0] <= (j))return true;
            }else{              //left_sum < right_sum
                diff = (right_sum - left_sum);
                iter = map_integer.find(diff);
                //chack the corners:
                //(b,b)
                //(0,b)
                //(0,j + 1)
                //(b,j + 1)
                if((grid.back().back() == diff) || (grid[0].back() == diff) || (grid.back()[j + 1] == diff) || (grid[0][j + 1] == diff))return true;
                else if(j == (grid[0].size() - 2) || (grid.size() == 1))continue;
                if(iter == map_integer.end())continue;
                if((*iter).second.j_interval[1] > (j))return true;
            }
        }
        return false;
   }
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        map<long long,_interger_interval> map_integer;
        vector<vector<long long>> map_rectsum(grid.size() + 1,vector<long long>(grid[0].size() + 1,0));
        //init
        for(int i = 1;i <= grid.size();++i){
            for(int j = 1;j <= grid[0].size();++j){
                map_rectsum[i][j] = map_rectsum[i - 1][j] + map_rectsum[i][j - 1] + grid[i - 1][j - 1] - map_rectsum[i - 1][j - 1];
                map<long long,_interger_interval>::iterator iter = map_integer.find(grid[i - 1][j - 1]);
                if(iter == map_integer.end()){
                    map_integer.insert({grid[i - 1][j - 1],_interger_interval(i - 1,j - 1)});
                }else{
                    (*iter).second.insert_new_num_pos(i - 1,j - 1);
                }
            }
        }
        if(chack_horizontal(grid,map_integer,map_rectsum))return true;
        if(chack_vertical(grid,map_integer,map_rectsum))return true;
        return false;
    }
};
int  main(){
    vector<vector<int>> g = {{5,5,6,2,2,2}};
    vector<vector<int>> g0 = {{1,2,4},{2,3,5}};
    vector<vector<int>> g3 = {{10},{86},{10}};
    Solution s;
    cout<< s.canPartitionGrid(g0);
}