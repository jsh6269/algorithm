#include <iostream>
#include <list>
using namespace std;
bool visited[8];

void DFS(list<int>* graph, int node){
    // time complexity: O(|V| + |E|)
    visited[node] = true;
    cout << node << " ";
    for(int adj_v : graph[node]){
        if(!visited[adj_v])
            DFS(graph, adj_v);
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

    fill_n(visited, 8, false);
    DFS(graph, 0);

    return 0;
}