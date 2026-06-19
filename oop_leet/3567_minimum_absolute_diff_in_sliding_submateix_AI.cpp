#include<bits/stdc++.h>
using namespace std;
/*prompt
this is a data structure that I used for the problem:
the problem is leetcode-3567 the link is down here:
https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix
please understand the code and finish the code of submatrix_diff_set::insert() and submatrix_diff_set::erase() in the file so the code can solve the problem.
and show the process in the comment
thanks in advance.
*/
class Solution {
    struct num_set_item{
        int frequency = 1;
        //this iteractor is pointed to the difference of 2 same numbers if there is.
        //if there is same numbers it would point to difference 0 in the map that store the distences.
        //if not, that the iterater is pointed to the .end() of the different map
        map<int,int>::iterator same_num_point;
        //this iteractor is pointed to the difference of this numbers and the next numbers in the map of numbers if there is.
        //if there is same numbers it would point to difference of this numbers and the next numbers;
        map<int,int>::iterator diff_num_point;
        num_set_item(map<int,int>& ds):same_num_point(ds.end()),diff_num_point(ds.end()){}
    };
    //this class is the data sturcture.
    //the reason that I use map is:
    //the problem is like: to find the minimum absolute distence of all the number, and a lot of requirement to insert or erase values such as when the matrix are "sliding"
    //there may be same numbers so I set a variable to store frequency of both distences and numbers
    class submatrix_diff_set{
        
        map<int,num_set_item> num_set_;
        map<int,int> diff_set;
        
        
    public:
        submatrix_diff_set(vector<vector<int>>& grid, int k){
            for(int i = 0;i < k;++i){
                for(int j = 0;j < k;++j){
                    this->insert(grid[i][j]);
                }
            }
        }
        //this function is used if a new number is inserted in the submatrix_diff_set
        //if there is the numbers that the set already have, It would increase the frequency of that
        //this function is not complete
        void insert(int num){
            auto it = num_set_.find(num);

            // CASE 1: number already exists → duplicate
            if(it != num_set_.end()){
                ++it->second.frequency;

                // If this is the SECOND occurrence → we must add diff = 0
                if(it->second.frequency == 2){
                    auto dit = diff_set.find(0);
                    if(dit == diff_set.end()){
                        dit = diff_set.insert({0, 0}).first;
                    }
                    ++dit->second;
                    it->second.same_num_point = dit;
                }
                return;
            }

            // CASE 2: new number insertion
            it = num_set_.insert({num, num_set_item(diff_set)}).first;

            auto prev_it = (it == num_set_.begin()) ? num_set_.end() : prev(it);
            auto next_it = next(it);

            // STEP 1: If both prev and next exist,
            // we are breaking (next - prev) into:
            // (num - prev) and (next - num)
            if(prev_it != num_set_.end() && next_it != num_set_.end()){
                int old_diff = next_it->first - prev_it->first;

                auto dit = diff_set.find(old_diff);
                if(dit != diff_set.end()){
                    if(--dit->second == 0) diff_set.erase(dit);
                }
            }

            // STEP 2: add (num - prev)
            if(prev_it != num_set_.end()){
                int d = num - prev_it->first;
                auto dit = diff_set.find(d);
                if(dit == diff_set.end()){
                    dit = diff_set.insert({d, 0}).first;
                }
                ++dit->second;
                prev_it->second.diff_num_point = dit;
            }

            // STEP 3: add (next - num)
            if(next_it != num_set_.end()){
                int d = next_it->first - num;
                auto dit = diff_set.find(d);
                if(dit == diff_set.end()){
                    dit = diff_set.insert({d, 0}).first;
                }
                ++dit->second;
                it->second.diff_num_point = dit;
            }
        }
        //this function is used if a new number is erased in the submatrix_diff_set
        //if after the erase there is no number that = num we remove the number in the number map
        //this function is not complete
       void erase(int num){
        auto it = num_set_.find(num);
        if(it == num_set_.end()) return;

        // CASE 1: multiple occurrences
        if(it->second.frequency > 1){
            --it->second.frequency;

            // If dropping from 2 → 1, remove diff = 0
            if(it->second.frequency == 1){
                auto dit = it->second.same_num_point;
                if(dit != diff_set.end()){
                    if(--dit->second == 0) diff_set.erase(dit);
                }
                it->second.same_num_point = diff_set.end();
            }
            return;
        }

        // CASE 2: removing last occurrence → full removal
        auto prev_it = (it == num_set_.begin()) ? num_set_.end() : prev(it);
        auto next_it = next(it);

        // STEP 1: remove (num - prev)
        if(prev_it != num_set_.end()){
            int d = num - prev_it->first;
            auto dit = diff_set.find(d);
            if(dit != diff_set.end()){
                if(--dit->second == 0) diff_set.erase(dit);
            }
        }

        // STEP 2: remove (next - num)
        if(next_it != num_set_.end()){
            int d = next_it->first - num;
            auto dit = diff_set.find(d);
            if(dit != diff_set.end()){
                if(--dit->second == 0) diff_set.erase(dit);
            }
        }

        // STEP 3: restore (next - prev) if both exist
        if(prev_it != num_set_.end() && next_it != num_set_.end()){
            int d = next_it->first - prev_it->first;
            auto dit = diff_set.find(d);
            if(dit == diff_set.end()){
                dit = diff_set.insert({d, 0}).first;
            }
            ++dit->second;
            prev_it->second.diff_num_point = dit;
        }

        num_set_.erase(it);
    }
        void right_slide(vector<vector<int>>& grid,int i,int j,int k){
            for(int l = 0;l < k;++l){
                this->erase(grid[i + l][j]);
                this->insert(grid[i + l][j + k]);
            }
        }
        void down_slide(vector<vector<int>>& grid,int i,int j,int k){
            for(int l = 0;l < k;++l){
                this->erase(grid[i][j + l]);
                this->insert(grid[i + k][j + l]);
            }
        }
        int get_minDiff(){
            return (*this->diff_set.begin()).first;
        }

    };
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        vector<vector<int>> out(grid.size() - k + 1,vector<int>(grid[0].size() - k + 1));
        submatrix_diff_set sds(grid,k),original_sds(grid,k);
        for(int j = 0;j < (grid[0].size() - k - 1);++j){
            out[0][j] = sds.get_minDiff();
            sds.right_slide(grid,0,j,k);
        }
        original_sds.down_slide(grid,0,0,k);
        out[0][grid[0].size() - k - 1] = sds.get_minDiff();
        for(int i = 1;i < (grid.size() - k);++i){
            sds = original_sds;
            for(int j = 0;j < (grid[0].size() - k - 1);++j){
                out[i][j] = sds.get_minDiff();
                sds.right_slide(grid,i,j,k);
            }
            out[i][grid[0].size() - k - 1] = sds.get_minDiff();
            original_sds.down_slide(grid,0,0,k);
        }
        return out;
    }
};
int main(){

}