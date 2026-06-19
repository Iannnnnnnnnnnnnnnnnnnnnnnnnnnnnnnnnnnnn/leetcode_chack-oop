#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    string getHappyString(int n, int k) {
        //if k > 3*2^(n - 1) ,we cant find k because there is only 3*2^(n - 1) many
        if(k > (3 << (n - 1)))return string();
        k--;//reuse k for k - 1
        //let k1 = k - 1
        string out;
        uint8_t first_ch = k >> (n - 1);
        //the first and second significant bit is the start character (00 = 'a,01 = 'b,10 = 'c)
        //if this is the k1-th laxicographically for length n of end char 'l' (k1 = 0 is the first)
        //we can get (2*k1)-th laxicographically for length n + 1 if we choose the laxicographically smaller char except 'l'
        //and get (2*k1) + 1 -th laxicographically for length n + 1 if we choose the laxicographically bigger char except 'l'
        //(n , k1) =  (n - 1 , k1/2) or (n , k1) =  (n - 1 , (k1 - 1)/2)
        //so k1 = 0110110 would be 01(first char),(= P*2 + 1)1,0(= P*2),1,1,0
        //the bits left is the choise taken:
        //0 is to choose the laxicographically smaller char except 'l',
        //1 is to choose the laxicographically bigger char except 'l'.
        out.push_back('a' + first_ch);
        for(int i = (n - 2);i >= 0; --i){
            //this is complicated...
            //how can we know what word are laxicographically smaller char except 'l' or laxicographically bigger char except 'l'.
            //we first map the vaild chars {a,b,c} onto {0,1,2}
            //choice is in {0,1}. 
            //'l' in {a,b,c} onto {0,1,2} and let l be the mapped form of the 'l', so l + c0 = 'l'
            //and a output number c in {0,1,2} => f(choise,l) = c
            //because the char cant repeat, so:
            //choice\l      |0      |1      |2
            //      0       |1      |0      |0
            //      1       |2      |2      |1
            //we can use mod to reduse the funtion into a addtion problem
            //choice\l      |0      |1      |2
            //      0       |1 mod 3|3 mod 3|3 mod 3
            //      1       |2 mod 3|2 mod 3|4 mod 3
            //we know c is almost (l + 1 + choise)mod 3 but fail at l = 1 because the output are inversed.
            //so we set l = 1 as an exception and use the fact that
            //if l == 1, l & 1 = 1
            //l & 1 = 0, otherwise
            //and use xor to inverse the result
            //so c = (l + 1 + choise^(l & 1)) mod 3
            //and c is reused of the form of l (first_ch) in the next stap (k >> i) & 1 is the choise
            out.push_back('a' + (first_ch = (first_ch + (1 + ((k >> i) & 1)) ^ (first_ch & 1)) % 3));
        }
        return out;
    }
};
int main(){
    Solution s;
    cout << s.getHappyString(10,100);
}