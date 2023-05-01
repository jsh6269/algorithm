#include <iostream>
#include <list>
using namespace std;

list<int> sorted;
bool visited[100];
void DFSTopologicalSort(list<int>*, int);

void topologicalSort(list<int>* graph, int n){
    // time complexity: O(|V|+|E|)
    for(int i=0; i<n; i++){
        if(!visited[i]){
            DFSTopologicalSort(graph, i);
        }
    }
}

void DFSTopologicalSort(list<int>* graph, int node){
    visited[node] = true;
    for(int adj_v : graph[node]){
        if(!visited[adj_v]){
            DFSTopologicalSort(graph, adj_v);
        }
    }
    sorted.push_front(node);
}

int main(){
    list<int> graph[11];
    graph[0].push_back(1);
    graph[0].push_back(3);
    graph[1].push_back(2);
    graph[3].push_back(4);
    graph[4].push_back(2);
    graph[4].push_back(5);
    graph[6].push_back(3);
    graph[6].push_back(7);
    graph[8].push_back(6);
    graph[8].push_back(9);
    graph[9].push_back(7);

    topologicalSort(graph, sizeof(graph)/sizeof(list<int>));
    for(int i : sorted){
        cout << i << " ";
    }
    return 0;
}