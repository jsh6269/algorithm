#include <iostream>
#include <list>
using namespace std;
static const int INF = 9999;

int** create2DArray(int height, int width=-1, int value=-1){
    int **arr;
    width = (width == -1) ? height : width;
    arr = (int**) malloc ( sizeof(bool*) * height);
    for(int i=0; i<height; i++){
        arr[i] = (int*) malloc ( sizeof(int) * width);
        for(int j=0; j<width; j++){
            arr[i][j] = value;
        }
    }
    return arr;
}

void freeArray(int **arr, int height){
    for(int i=0; i<height; i++){
        free(arr[i]);
    }
    free(arr);
}

bool dfs(int start, int sink, list<int>* graph, int** capacity, int** flow, int* path, bool* visited){
    if(start == sink){
        return true;
    }
    visited[start] = true;
    for(int next : graph[start]){
        if(!visited[next] && capacity[start][next] > flow[start][next]){
            path[next] = start;
            bool flag = dfs(next, sink, graph, capacity, flow, path, visited);
            if(flag){
                return true;
            }
        }
    }
    return false;
}

int fordFulkerson(int source, int sink, int n, list<int>* graph, int** capacity){
    // time complexity: O((V+E)F)
    // F: maximum amount of possible flow
    int totalFlow = 0;
    int* path = (int*) malloc(sizeof(int) * 100);
    bool* visited = (bool*) malloc(sizeof(bool) * 100);
    int** flow = create2DArray(n, n, 0);
    fill_n(path, 100, -1);

    while(dfs(source, sink, graph, capacity, flow, path, visited)){
        int _flow = INF;
        for(int i=sink; i!= source; i=path[i]){
            int from = path[i], to = i;
            _flow = min(_flow, capacity[from][to] - flow[from][to]);
        }
        for(int i=sink; i!=source; i=path[i]){
            int from = path[i], to = i;
            flow[from][to] += _flow;
            flow[to][from] -= _flow;
        }
        totalFlow += _flow;
        fill_n(path, 100, -1);
        fill_n(visited, 100, false);
    }
    free(path);
    free(visited);
    freeArray(flow, n);
    return totalFlow;
}


int main(){
    list<int> graph[8];
    graph[0].push_back(1); graph[0].push_back(2); graph[0].push_back(3);
    graph[1].push_back(0); graph[1].push_back(4); graph[1].push_back(5);
    graph[2].push_back(0); graph[2].push_back(5);
    graph[3].push_back(0); graph[3].push_back(6);
    graph[4].push_back(1); graph[4].push_back(7);
    graph[5].push_back(1); graph[5].push_back(2); graph[5].push_back(6); graph[5].push_back(7);
    graph[6].push_back(3); graph[6].push_back(5); graph[6].push_back(7);
    graph[7].push_back(4); graph[7].push_back(5); graph[7].push_back(6);

    int** capacity = create2DArray(8, 8, 0);
    capacity[0][1] = 3; capacity[0][2] = 4; capacity[0][3] = 5;
    capacity[1][4] = 1; capacity[1][5] = 3;
    capacity[2][5] = 2;
    capacity[3][6] = 7;
    capacity[4][7] = 3;
    capacity[5][7] = 5;
    capacity[6][5] = 1; capacity[6][7] = 4;

    cout << fordFulkerson(0, 7, 8, graph, capacity);
    freeArray(capacity, 8);
    return 0;
}