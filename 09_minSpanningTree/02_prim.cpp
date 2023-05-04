#include <iostream>
#include <list>
#include <queue>
#include <tuple>
using namespace std;

struct comp {
    constexpr bool operator()(tuple<int, int, int> const& a, tuple<int, int, int> const& b) const noexcept{
        return get<2>(a) > get<2>(b);
    }
};

pair<int, list<pair<int, int>>> prim(list<pair<int, int>>* graph, int n){
    // optimal time complexity is close to O(VlogE) or O(ElogE)
    // greedy algorithm (verified)
    int mstLen = 0;
    bool visited[n];
    fill_n(visited, n, false);
    // edge starts from get<0>q to get<1>q and its cost is get<2>q
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, comp> q;
    list<pair<int, int>> spanEdge;

    visited[0] = true;
    for(auto p : graph[0]){
        q.emplace(0, p.first, p.second);
    }
    while(!q.empty()){
        // looks like this loops for O(E) times
        tuple<int, int, int> t = q.top();
        q.pop();
        int beginPt = get<0>(t), endPt = get<1>(t), len = get<2>(t);
        if(!visited[endPt]){
            // looks like this portion is executed total O(V) times
            visited[endPt] = true;
            mstLen += len;
            spanEdge.emplace_back(beginPt, endPt);
            for(auto p : graph[endPt]){
                if(!visited[p.first])
                    // looks like this single push takes O(logE)
                    // total num of push doesn't exceed 2|E|
                    q.emplace(endPt, p.first, p.second);
            }
        }
    }
    return make_pair(mstLen, spanEdge);
}

int main(){
//    int graphArray[7][7] = {{0, 7, -1, -1, 4, -1, -1},
//                        {7, 0, 2, 11, -1, -1, -1},
//                        {-1, 2, 0, 10, 7, 5, -1},
//                        {-1, 11, 10, 0, -1, 1, 9},
//                        {4, -1, 7, -1, 0, 2, -1},
//                        {-1, -1, 5, 1, 2, 0, -1},
//                        {-1, -1, -1, 9, -1, -1, 0}};

    list<pair<int, int>> graph[7];
    graph[0].emplace_back(1,7);
    graph[0].emplace_back(4,4);
    graph[1].emplace_back(0,7);
    graph[1].emplace_back(2,2);
    graph[1].emplace_back(3,11);
    graph[2].emplace_back(1,2);
    graph[2].emplace_back(3,10);
    graph[2].emplace_back(4,7);
    graph[2].emplace_back(5,5);
    graph[3].emplace_back(1,11);
    graph[3].emplace_back(2,10);
    graph[3].emplace_back(5,1);
    graph[3].emplace_back(6,9);
    graph[4].emplace_back(0,4);
    graph[4].emplace_back(2,7);
    graph[4].emplace_back(5,2);
    graph[5].emplace_back(2,5);
    graph[5].emplace_back(3,1);
    graph[5].emplace_back(4,2);
    graph[6].emplace_back(3,9);

    pair<int, list<pair<int, int>>> ans = prim(graph, 7);
    cout << ans.first << endl;
    for(auto p : ans.second){
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    return 0;
}