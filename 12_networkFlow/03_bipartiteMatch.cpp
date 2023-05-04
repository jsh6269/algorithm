#include <iostream>
#include <list>
#include <queue>
using namespace std;

bool dfs(int node, list<int>* graph, bool* done, int* owner){
    // time complexity: O(VE)
    for(int adj : graph[node]){
        if(done[adj]){
            continue;
        }
        done[adj] = true;
        if(owner[adj] == -1 || dfs(owner[adj], graph, done, owner)){
            owner[adj] = node;
            return true;
        }
    }
    return false;
}

int main(){
    list<int> graph[5];
    graph[0].push_back(0);
    graph[0].push_back(2);
    graph[0].push_back(4);
    graph[1].push_back(0);
    graph[1].push_back(1);
    graph[2].push_back(4);
    graph[3].push_back(2);
    graph[4].push_back(1);

    bool done[5];
    int owner[5];
    int cnt = 0;
    fill_n(owner, 5, -1);
    for(int i=0; i<5; i++){
        fill_n(done, 5, false);
        if(dfs(i, graph, done, owner)){
            cnt++;
        }
    }
    cout << cnt << endl;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    for(int i=0; i<5; i++){
        pq.emplace(owner[i], i);
    }
    while(!pq.empty()){
        if(pq.top().first != -1){
            cout << pq.top().first << " => " << pq.top().second << endl;
        }
        pq.pop();
    }
    return 0;
}
