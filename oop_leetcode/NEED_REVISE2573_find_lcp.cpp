#include<bits/stdc++.h>
using namespace std;
class Solution {
    struct _disjoint_set_union{
        _disjoint_set_union* upper = nullptr;
        int rank = 0;
        int value = -1;
        _disjoint_set_union* head(){
            _disjoint_set_union* n = this;
            while (n->upper != nullptr){
                n = n->upper;
            }
            return n;
        }
        bool connect(_disjoint_set_union& dest){
            _disjoint_set_union* l = this->head();
            _disjoint_set_union* r = dest.head();
            if(l == r)return false;
            if(l->rank > r->rank){
                r->upper = l;
            }else if(l->rank < r->rank){
                l->upper = r;
            }else{
                l->upper = r;
                r->rank++;
            }
            return true;
        }
    };
    bool _is_valid_lcp(vector<vector<int>>& lcp,int n){
        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                if(lcp[i][j] == 0)continue;
                if(((i >= (n - 1)) || (j >= (n - 1))) && (lcp[i][j] > 1))return false;
                if((i < (n - 1)) && (j < (n - 1)) && ( ((lcp[i][j] - 1) != lcp[i + 1][j + 1]))){
                    return false;
                }
            }
        }
        return true;
    }
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        if(!_is_valid_lcp(lcp,n))return string();
        vector<_disjoint_set_union> num_DSU(n ,_disjoint_set_union());
        vector<int> num_classify(n ,0);
        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                if(lcp[i][j] == 0){
                    continue;
                }
                num_DSU[n - i - 1].connect(num_DSU[n - j - 1]);
            }
        }
        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                if(lcp[i][j] != 0)continue;
                if(num_DSU[n - i - 1].head() == num_DSU[n - j - 1].head())return string();
            }
        }
        int count = 0;
        _disjoint_set_union* head_now = nullptr;
        //why?
        for(int i = n;i > 0;--i){
            head_now = num_DSU[i - 1].head();
            if(head_now->value == -1){
                head_now->value = ++count;
            }
            num_classify[i - 1] = head_now->value;
        }
        //so this would heppen
        if(count > 26)return string();
        string out;
        for(int i = lcp[0][0];i > 0 ;--i){
            out.push_back('a' + (num_classify[i - 1] - 1));
        }
        return out;
    }
};
int main(){
    vector<vector<int>> a ={ {4,0,2,0},{0,3,0,1},{2,0,2,0},{0,1,0,1}};
    vector<vector<int>> b = {{2,0},{1,1}};
    Solution s;
    cout << s.findTheString(b);
}