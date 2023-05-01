#include <iostream>
#include <tuple>
#include <queue>
using namespace std;
const int INF = 9999;

int** create2DArray(int height, int width=-1){
    int **arr;
    width = (width == -1) ? height : width;
    arr = (int**) malloc ( sizeof(int*) * height);
    for(int i=0; i<height; i++){
        arr[i] = (int*) malloc ( sizeof(int) * width);
        for(int j=0; j<width; j++){
            arr[i][j] = INF;
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

tuple<int*, int*, bool> bellmanFord(int** graph, int n, int startNode){
    // time complexity: O(|V||E|)
    queue<int> q;
    int* inQueue = (int*) malloc(sizeof(int) * n);
    int* dist = (int*) malloc(sizeof(int) * n);
    int* pred = (int*) malloc(sizeof(int) * n);

    for(int v=0; v<n; v++){
        pred[v] = -1;
        if(v != startNode){
            dist[v] = INF;
            inQueue[v] = false;
        }
        else{
            dist[v] = 0;
        }
    }
    q.push(startNode);
    inQueue[startNode] = true;
    q.push(-1);

    int i = 0;
    while(q.size() != 1 && i < n){
        int u = q.front();
        q.pop();
        if(u == -1){
            i++;
            q.push(-1);
        }
        else{
            inQueue[u] = false;
            for(int v=0; v<n; v++){
                if(graph[u][v] != INF && dist[v] > dist[u] + graph[u][v]){
                    dist[v] = dist[u] + graph[u][v];
                    pred[v] = u;
                    if(!inQueue[v]){
                        q.push(v);
                        inQueue[v] = true;
                    }
                }
            }
        }
    }
    return make_tuple(dist, pred, i < n);
}

int main(){
    int exArr[24][3] = {{0,3,1},{1,1,2},{2,4,3},{0,5,4},
                        {1,9,5},{2,2,6},{3,6,7},{4,3,5},
                        {5,5,6},{6,8,7},{4,7,8},{5,9,9},
                        {6,3,10},{7,2,11},{8,8,9},{9,4,10},
                        {10,6,11},{8,6,12},{9,4,13},{10,3,14},
                        {11,3,15},{12,3,13},{13,2,14},{14,7,15}};

    // case 1
    int** example1 = create2DArray(16);
    for(auto & p : exArr){
        example1[p[0]][p[2]] = p[1];
        example1[p[2]][p[0]] = p[1];
    }
    tuple<int*, int*, bool> ans1 = bellmanFord(example1, 16, 0);
    cout << get<0>(ans1)[15] << endl;
    freeArray(example1, 16);

    // case 2
    int** example2 = create2DArray(4);
    example2[0][1] = 5;
    example2[1][2] = -4;
    example2[2][3] = 1;
    example2[0][3] = 3;
    example2[0][2] = 4;
    tuple<int*, int*, bool> ans2 = bellmanFord(example2, 4, 0);
    cout << get<0>(ans2)[3] << endl;
    freeArray(example2, 4);

    return 0;
}