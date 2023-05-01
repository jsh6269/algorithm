#include <iostream>
#include <utility>
#include <queue>
const int INF = 9999;
using namespace std;

class compare {
public:
    bool operator()(pair<int, int> o1, pair<int, int> o2){
        return o1.second > o2.second;
    }
};
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

pair<int*, int*> dijkstra(int** graph, int n, int startNode){
    // time complexity: O(n^2)
    int* dist = (int*) malloc(sizeof(int) * n);
    int* pred = (int*) malloc(sizeof(int) * n);
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;

    for(int v=0; v<n; v++){
        pred[v] = -1;
        dist[v] = (v == startNode) ? 0 : INF;
        pq.emplace(v, dist[v]);
    }
    while(!pq.empty()){
        pair<int, int> minPair = pq.top();
        pq.pop();

        int u = minPair.first;
        if(dist[u] < minPair.second){
            continue;
        }

        for(int v=0; v<n; v++){
            if(graph[u][v] != INF && dist[v] > dist[u] + graph[u][v]){
                dist[v] = dist[u] + graph[u][v];
                pred[v] = u;
                pq.emplace(v, dist[v]);
            }
        }
    }
    return make_pair(dist, pred);
}

int main(){
    int exArr[24][3] = {{0,3,1},{1,1,2},{2,4,3},{0,5,4},
                           {1,9,5},{2,2,6},{3,6,7},{4,3,5},
                           {5,5,6},{6,8,7},{4,7,8},{5,9,9},
                           {6,3,10},{7,2,11},{8,8,9},{9,4,10},
                           {10,6,11},{8,6,12},{9,4,13},{10,3,14},
                           {11,3,15},{12,3,13},{13,2,14},{14,7,15}};
    int** example = create2DArray(16);
    for(auto & p : exArr){
        example[p[0]][p[2]] = p[1];
        example[p[2]][p[0]] = p[1];
    }

    int cnt = 0;
    pair<int*, int*> myPair = dijkstra(example, 16, 0);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cout << myPair.first[cnt++] << " ";
        }
        cout << endl;
    }
    free(myPair.first);
    free(myPair.second);
    freeArray(example, 16);
    return 0;
}