#include <iostream>
#include <queue>
#include <tuple>
#include <list>
using namespace std;

struct compare{
    bool operator()(tuple<int, int, int>a, tuple<int, int, int>b){
        return get<2>(a) > get<2>(b);
    }
};

list<int> activitySelection(int* start, int* finish, int n){
    // time complexity: O(nlogn)
    // greedy algorithm (verified)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, compare> pq;
    list<int> selectedID;
    for(int i=0; i<n; i++){
        pq.emplace(i, start[i], finish[i]);
    }
    int lastHour = 0;
    while(!pq.empty()){
        tuple<int, int, int> item = pq.top();
        pq.pop();
        if(lastHour <= get<1>(item)){
            selectedID.emplace_back(get<0>(item));
            lastHour = get<2>(item);
        }
    }
    return selectedID;
}

int main(){
    char names[11] = {'A','B','C','D','E','F','G','H','I','J','K'};
    int start[11] = {1,3,0,5,3,5,6,8,8,2,12};
    int finish[11] = {4,5,6,7,9,9,10,11,12,14,16};

    list<int> ans = activitySelection(start, finish, 11);
    for(int i : ans){
        cout << names[i] << ": " << start[i] << " ~ " << finish[i] << endl;
    }
    return 0;
}