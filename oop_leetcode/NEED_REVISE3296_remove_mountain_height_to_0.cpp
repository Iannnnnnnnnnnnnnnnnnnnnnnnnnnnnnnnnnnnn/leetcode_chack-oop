#include<bits/stdc++.h>
using namespace std;
class Solution {
    inline long long remove_maxheight(int worker_i_Times,long long maxTime){
        //time complexity: O(log(s))
        //using binery search to find removerable maxheight
        //sqrt is not precise enough for this big num
        long long ll = 0,rr = maxTime + 1,mid,reqtime;
        while ((rr - ll) > 1){
            mid = ll + ((rr - ll) >> 1);
            //avoiding long long overflow
            if(((((INT64_MAX/mid)/(mid + 1)) << 1) < worker_i_Times)){
                rr = mid;
                continue;
            }
            reqtime = (worker_i_Times*((mid*(mid + 1)) >> 1));
            if(reqtime > maxTime){
                rr = mid;
            }else if(reqtime < maxTime){
                ll = mid;
            }else{
                return mid;
            }
        }
        return ll;
        
    }
    long long max_remove_height_in_time(long long time,vector<int>& workerTimes){
        long long rmed_height = 0;
        for(int i = 0;i < workerTimes.size();i++){
            rmed_height += remove_maxheight(workerTimes[i],time);
        }
        return rmed_height;
    }
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        //long long rr = (long long)(1e10) + 1,ll = 1,mid;
        long long rr = 7,ll = 0,mid;
        //O(nlog(s)) = O(nlog(max(times*n)))
        //O(nlog(n))
        while ((rr - ll) > 1){
            mid = ll + ((rr - ll) >> 1);
            if(max_remove_height_in_time(mid,workerTimes) >= mountainHeight){
                rr = mid;
            }else{ //max_remove_height_in_time(mid,workerTimes) <= mountainHeight
                ll = mid;
            }
        }
        return ll + 1;
    }
};
int main(){
    Solution s;
    vector<int> v ={1};
    cout << s.minNumberOfSeconds(1,v);
}