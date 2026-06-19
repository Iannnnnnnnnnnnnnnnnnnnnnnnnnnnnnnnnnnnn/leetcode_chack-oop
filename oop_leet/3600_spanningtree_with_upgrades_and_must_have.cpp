#include<bits/stdc++.h>
using namespace std;
class Solution {
    static bool cmp(const vector<int> &a,const vector<int> &b){
        //placing must = 1 at the front
        if(a[3] == b[3]){
            return a[2] > b[2];
        }
        return a[3] > b[3];
        
    }
    struct DSU{
        //{upper,rank}
        //the head of a dsu is itself
        vector<vector<int>> vec_nodes;
        DSU(int n){
            vec_nodes.resize(n,{-1,0});
            for(int i = 0;i < n;i++){
                vec_nodes[i][0] = i;
            }
        }
        int find_head(int x){
            while (vec_nodes[x][0] != x ){
                x = vec_nodes[x][0];
            }
            return x;
        }
        //0: fail to merge because both dsu are the same;
        //1: success
        bool merge(int x,int y){
            int s1 = find_head(x),s2 = find_head(y);
            if(s1 == s2){
                return false;
            }
            //we have rank that is the maximum search depth of a DSU
            //we put the upper of the head of the DSU which had smaller rank.
            //if the rank are the same we increase one of two DSU's rank by one
            //so that the rank never excceed log2(n);
            if(vec_nodes[s1][1] > vec_nodes[s2][1]){
                vec_nodes[s2][0] = s1;
            }else if(vec_nodes[s1][1] < vec_nodes[s2][1]){
                vec_nodes[s1][0] = s2;
            }else{
                vec_nodes[s1][0] = s2;
                vec_nodes[s2][1]++;
            }
            return true;
        }
    };
    //the dsu dont pass by ref
    //because we need the same original DSU for each candidates of target_stability
    //0: not enough upgrades
    //1: not enough upgrades
    int krustal(int n,int nonMust_start_point,int connected_segs ,vector<vector<int>>& edges, int k,long long target_stability,DSU set_searching){
        //kruskal algorithm 
        //for largest stablity to smallest
        //we can add a sides to form s MST
        //but if 2*stability < target_stability
        //we does not choose it
        int update_used = 0;
        int successful_merge = 0;
        for(int i = nonMust_start_point;i < edges.size();++i){
            if(connected_segs == 1)return update_used <= k;
            if((edges[i][2] << 1) < target_stability){
                continue;
            }else if(edges[i][2] >= target_stability){
                successful_merge = set_searching.merge(edges[i][0],edges[i][1]);
                connected_segs -= successful_merge;
            }else{          // edges[i][2] < target_stability <= edges[i][2]*2
                successful_merge = set_searching.merge(edges[i][0],edges[i][1]);
                update_used += successful_merge;
                connected_segs -= successful_merge;
            }
        }
        if(update_used > k)return 0;
        if(connected_segs == 1)return 1;
        
        return 0;
    }
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        //edges[i] = {s,e,st,must}
        //we sort the array with decreasing stability;
        sort(edges.begin(),edges.end(),cmp);
        DSU set_searching(n);
        //this is min(those edges that must == 1)
        long long most_not_upgradeable_stability = (long long)(1e5)*n;
        int connected_segs = n;
        //this index is the
        int index = 0;
        for( ;(index < edges.size()) && (edges[index][3] == 1);++index){
            //if must form a loop
            if(set_searching.merge(edges[index][0],edges[index][1]) == 0)return -1;
            connected_segs--;
            most_not_upgradeable_stability = min(most_not_upgradeable_stability,(long long)edges[index][2]);
        }
        //if the graph is not even connected
        if(krustal(n,index,connected_segs,edges,k,0,set_searching) == 0)return -1;
        int ll = 1,rr = most_not_upgradeable_stability + 1;
        
        while ((rr - ll) > 1){
            int mid = ll + ((rr - ll) >> 1);
            if(krustal(n,index,connected_segs,edges,k,mid,set_searching)){
                ll = mid;
            }else{
                rr = mid;
            }

        }
        return ll;
    }
};
int main(){
    int n = 3,k = 2;
    vector<vector<int>> edges = {{0,1,27955,0},{0,2,96441,1},{1,2,13682,1}};
    //vector<vector<int>> edges = {{0,1,4,0},{1,2,3,0},{0,2,1,0}};
    Solution s;
    cout<<s.maxStability(n,edges,k);
}