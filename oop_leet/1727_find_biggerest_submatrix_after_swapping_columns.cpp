#include<bits/stdc++.h>
using namespace std;
class Solution {
    static bool cmp(const int& a,const int &b){
        //if true, a would be placing forward than b;
        return a > b;
    }
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        //we only use 2 arrays to repersent next_sum and now_sum
        //so we need a alternating number for each row
        //i & 1 which is the last bit of i is a great choise
        //we let i & 1 to represent next_sum
        //now_sum is not next sum, which is, !(i & 1)
        vector<vector<int>> cumulative_1s_row(2,vector<int>(matrix[0].size(),0));
        //store the cumulative 1s for each column
        //that is like store:
        //3,2,4,1.0
        //00100
        //10100
        //11100
        //11110
        //because we can rearrange the columns into any order
        //we sort the numbers into descending order
        //and look the maxinum of c[j]*[j] (area)
        //10000 -> j
        //11000
        //11100
        //11110
        //time complexity O(nmlog(n));
        int _max_area = 0;
        for(int j = 0;j < matrix[0].size();++j){
            cumulative_1s_row[0 & 1][j] += matrix[0][j];
        }
        for(int i = 1;i < matrix.size();++i){
            for(int j = 0;j < matrix[0].size();++j){
                if(matrix[i][j])cumulative_1s_row[i & 1][j] = (cumulative_1s_row[!(i & 1)][j] + 1);
                else cumulative_1s_row[i & 1][j] = 0;
            }
            sort(cumulative_1s_row[!(i & 1)].begin(),cumulative_1s_row[!(i & 1)].end(),cmp);
            for(int j = 0;j < matrix[0].size();++j){
                _max_area = max(_max_area,(j + 1)*cumulative_1s_row[!(i & 1)][j]);
            }
        }
        sort(cumulative_1s_row[!(matrix.size() & 1)].begin(),cumulative_1s_row[!(matrix.size() & 1)].end(),cmp);
        for(int j = 0;j < matrix[0].size();++j){
            _max_area = max(_max_area,(j + 1)*cumulative_1s_row[!(matrix.size() & 1)][j]);
        }
        return _max_area;
    }
};
int main(){
    Solution s;
    vector<vector<int>> mat = {{0,0,1},{1,1,1},{1,0,1}};
    cout << s.largestSubmatrix(mat);
}