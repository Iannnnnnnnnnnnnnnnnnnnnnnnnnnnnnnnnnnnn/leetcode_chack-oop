#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        //get the last '1' in each row to see the "length of main diangal blockage" 
        list<int> last_one_position;
        for(int i = 0;i < grid.size();i++){
            for(int j = grid[i].size();;j--){
                //if j = 0 [j - 1] would cause undefined behavior
                //there exist a row that is all zeros
                if((j == 0) || (grid[i][j - 1] == 1)){
                    last_one_position.push_back(j);
                    break;
                }
            }
        }
        int count = 0;
        //for each required min last position, it need the leftmost value that not bigger then req_min_length.
        //for optimiszation
        //and if found, we need to remove that number for showing that the number is moved 
        for(int req_min_length = 1; req_min_length <= grid.size() ; ++req_min_length){
            for(list<int>::iterator i = last_one_position.begin();;i++ ){
                //if not found means the form is not reachable
                if(i == last_one_position.end())return -1;
                if(*i <= req_min_length){
                    last_one_position.erase(i);
                    break;
                }
                count++;
            }
        }
        return count;
    }   
};
int main(){
    vector<vector<int>> grid = {{0,0},{0,1}};
    Solution s;
    cout << s.minSwaps(grid) << '\n';
}