#include<bits/stdc++.h>
using namespace std;
class Fancy {
    vector<int> seq;
    long long multi_num = 1;
    long long add_num = 0;
    //the time complexity of this is O(log2(1e9 + 7)) would be O(1)
    long long modularInverse_1e9p7(long long a){
        //a_{-1} = a^{m - 2}
        int m = (int)1e9 + 5;
        long long res = 1;
        while (m){
            if(m & 1)res = (res * a)%((long long)1e9 + 7);
            a = (a * a)%((long long)1e9 + 7);
            m >>= 1;
        }
        return res;
    }
public:
    Fancy() {
        multi_num = 1;
        add_num = 0;
    }
    void append(int val) {
        //because we need to add a number X1 
        //but if we need to output X1
        //we need a num T that X1 = KT + A
        //(X1 - A)*K^{-1} = T (mod 1e9 + 7)
        //so we need the modular inverse of K for 10^9 + 7
        seq.push_back((((long long)val + (((long long)1e9 + 7) - this->add_num)%((long long)1e9 + 7)) * modularInverse_1e9p7(this->multi_num))%((long long)1e9 + 7));
    }
    
    void addAll(int inc) {
        //we give 2 nums K and A
        //if we need to give the value of x;
        //give Kx + A
        //if all add A2 => Kx + (A + A2) -> new A
        this->add_num = (this->add_num + inc)%((long long)1e9 + 7);
    }
    
    void multAll(int m) {
        //if all multiply m => (Kx + A)*m = mKx + mA -> new A
        this->add_num = (this->add_num * m)%((long long)1e9 + 7);
        this->multi_num = (this->multi_num * m)%((long long)1e9 + 7);
    }
    
    int getIndex(int idx) {
        if(idx >= this->seq.size())return -1;
        return (int)((((seq[idx] * multi_num)%((long long)1e9 + 7)) + add_num)%((long long)1e9 + 7));
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
int main(){
    Fancy f;
    f.append(2);
    f.addAll(3);
    f.multAll(2);
    cout<< f.getIndex(0);
}