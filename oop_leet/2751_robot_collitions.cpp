#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        //the stack that keep the robots that have the potential
        //{index,health}
        stack<pair<int,int>> r_way_robots;
        vector<int> survived_robots_healths(positions.size(),-1);
        vector<int> output;
        map<int,int> number_positions;
        for(int i = 0;i < positions.size();++i){
            number_positions.insert({positions[i],i});
        }
        for(map<int,int>::iterator i = number_positions.begin();i != number_positions.end();i++){
            //the robots if directions are different would eventually collide
            //we see the partial solutions where there is only robot[0],robot[1], ... ,robot[i] (i + 1 robot counted from left to right)
            //the basic case is that only one robots
            //if the leftmost robot is going to the left then it wont collide
            //else that it have the potential of collition
            //if the colliding result of i
            if(directions[(*i).second] == 'R'){
                r_way_robots.push({(*i).second,healths[(*i).second]});
                continue;
            }
            if(r_way_robots.empty()){
                survived_robots_healths[(*i).second] = healths[(*i).second];
                continue;
            }
            //this is colliding
            //either all the right way is destoryed
            //notice: there is no need to consider the case that a robot have its health redused to 0;
            int colliding_health = healths[(*i).second];
            while (!r_way_robots.empty()){
                if(colliding_health > r_way_robots.top().second){
                    r_way_robots.pop();
                    colliding_health--;
                }else if(colliding_health < r_way_robots.top().second){
                    colliding_health = -1;
                    r_way_robots.top().second--;
                    break;
                }else{ //colliding_health == r_way_robots.top().second
                    colliding_health = -1;
                    r_way_robots.pop();
                    break;
                }
            }
            if(colliding_health == -1){
                //not survived;
                continue;
            }
            survived_robots_healths[(*i).second] = colliding_health;
        }
        while (!r_way_robots.empty()){
            survived_robots_healths[r_way_robots.top().first] = r_way_robots.top().second;
            r_way_robots.pop();
        }
        for(int i = 0;i < survived_robots_healths.size();++i){
            if(survived_robots_healths[i] == -1)continue;
            output.push_back(survived_robots_healths[i]);
        }
        return output;
    }
};