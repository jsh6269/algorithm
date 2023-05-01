#include <iostream>
#include <list>
#include <stack>
using namespace std;

void DFS(list<int>* graph, int node){
    // time complexity: O(|V| + |E|)
    stack<int> S;
    bool visited[8];
    bool inStack[8];

    fill_n(visited, 8, false);
    fill_n(inStack, 8, false);

    S.push(node);
    inStack[node] = true;

    while(!S.empty()){
        int c = S.top();
        S.pop();
        inStack[c] = false;
        visited[c] = true;
        cout << c << " ";

        for(int adj_v : graph[c]){
            if(!visited[adj_v] && !inStack[adj_v]){
                S.push(adj_v);
                inStack[adj_v] = true;
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


    DFS(graph, 0);

    return 0;
}