#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        //worse way usually have its place
        vector<vector<vector<int>>> dp_coins_path(coins.size(),vector<vector<int>>(coins[0].size(),vector<int>(3,INT_MIN)));
        //the max coins that the robot can collect from (0,0) to (i - 1,j - 1) and neutualized k robbers on the way
        //because using n + 1,m + 1 would cause problem because 0 > -1
        //if the matrixs are all < 0 it would return 0 instead of the maxinums of the negative
         
         dp_coins_path[0][0][0] = coins[0][0];
        if(coins[0][0] >= 0){
            for(int k = 1; k < 3;k++){
                dp_coins_path[0][0][k] = coins[0][0];
            }   
        }else{
            for(int k = 1; k < 3;k++){
                dp_coins_path[0][0][k] = 0;
            }
        }
           
        for(int i = 1;i < coins.size();i++){
            dp_coins_path[i][0][0] = coins[i][0] + dp_coins_path[i - 1][0][0];
            if(coins[i][0] < 0){
                for(int k = 1; k < 3;k++){
                    dp_coins_path[i][0][k] = max(coins[i][0] + dp_coins_path[i - 1][0][k],dp_coins_path[i - 1][0][k - 1]);
                }
            }else{
                for(int k = 1; k < 3;k++){
                    dp_coins_path[i][0][k] = coins[i][0] + dp_coins_path[i - 1][0][k];
                }
            }
            
        }
        for(int j = 1;j < coins[0].size();++j){
            dp_coins_path[0][j][0] = coins[0][j] + dp_coins_path[0][j - 1][0];
            if(coins[0][j] < 0){
                for(int k = 1; k < 3;k++){
                    dp_coins_path[0][j][k] = max(coins[0][j] + dp_coins_path[0][j - 1][k],dp_coins_path[0][j - 1][k - 1]);
                }
            }else{
                for(int k = 1; k < 3;k++){
                    dp_coins_path[0][j][k] = coins[0][j] + dp_coins_path[0][j - 1][k];
                }
            }
        }
        for(int i = 1;i < coins.size();i++){
            for(int j = 1;j < coins[0].size();++j){
                if(coins[i][j] >= 0){
                    for(int k = 0; k < 3;k++){
                        //+1 is because it needs (i,j)
                        dp_coins_path[i][j][k] = coins[i][j] + max(dp_coins_path[i][j - 1][k],dp_coins_path[i - 1][j][k]);
                    }
                }else{
                    dp_coins_path[i][j][0] = coins[i][j] + max(dp_coins_path[i][j - 1][0],dp_coins_path[i - 1][j][0]);
                    for(int k = 1; k < 3;k++){
                        //+1 is because it needs (i,j)
                        dp_coins_path[i][j][k] = 
                            max(
                                max(dp_coins_path[i - 1][j][k - 1],dp_coins_path[i][j - 1][k - 1]),     /*if we choose to neutualize*/
                                coins[i][j] + max(dp_coins_path[i - 1][j][k],dp_coins_path[i][j - 1][k])/*if we choose to take the loss*/
                            );
                    }
                }
                
            }
        }
        int a =0;
        return *max_element(dp_coins_path.back().back().begin(),dp_coins_path.back().back().end());
    }
};
int main(){
    vector<vector<int>> c = {{6,-14,6},{-17,-16,17},{4,4,-6}};
    Solution s;
    cout << s.maximumAmount(c);
}