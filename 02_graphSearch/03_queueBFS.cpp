#include <iostream>
#include <list>
#include <queue>
using namespace std;

void BFS(list<int>* graph, int node){
    // time complexity: O(|V| + |E|)
    queue<int> Q;
    bool visited[8];
    bool inQueue[8];

    fill_n(visited, 8, false);
    fill_n(inQueue, 8, false);

    Q.push(node);
    inQueue[node] = true;

    while(!Q.empty()){
        int c = Q.front();
        Q.pop();
        inQueue[c] = false;
        visited[c] = true;
        cout << c << " ";

        for(int adj_v : graph[c]){
            if(!visited[adj_v] && !inQueue[adj_v]){
                Q.push(adj_v);
                inQueue[adj_v] = true;
            }
        }
    }
}

int main(){
    list<int> graph[8];
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[0].push_back(3);
    graph[1].push_back(0);
    graph[1].push_back(4);
    graph[2].push_back(0);
    graph[3].push_back(0);
    graph[3].push_back(5);
    graph[4].push_back(1);
    graph[4].push_back(5);
    graph[5].push_back(3);
    graph[5].push_back(4);
    graph[5].push_back(6);
    graph[5].push_back(7);
    graph[6].push_back(5);
    graph[7].push_back(5);


    BFS(graph, 0);

    return 0;
}