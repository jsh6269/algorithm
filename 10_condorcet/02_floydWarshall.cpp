#include <iostream>
#include <utility>
using namespace std;

int** create2DArray(int height, int width=-1){
    int **arr;
    width = (width == -1) ? height : width;
    arr = (int**) malloc ( sizeof(int*) * height);
    for(int i=0; i<height; i++){
        arr[i] = (int*) malloc ( sizeof(int) * width);
    }
    return arr;
}


pair<int**, int**> floydMarshall(int** W, int n){
    // time complexity: O(n^3)
    int** dist = create2DArray(n);
    int** pred = create2DArray(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(W[i][j] != 0){
                dist[i][j] = W[i][j];
                pred[i][j] = i;
            }
            else{
                dist[i][j] = 999;
                pred[i][j] = -1;
            }
        }
    }
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            if(i != k){
                for(int j=0; j<n; j++){
                    if(j != i && dist[i][j] > dist[i][k] + dist[k][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                        pred[i][j] = pred[k][j];
                    }
                }
            }
        }
    }
    return make_pair(dist, pred);
}

void freeArray(int **arr, int height){
    for(int i=0; i<height; i++){
        free(arr[i]);
    }
    free(arr);
}

int main(){
    int** graph = create2DArray(4);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            graph[i][j] = 0;
        }
    }
    graph[0][1] = 5;
    graph[1][2] = -4;
    graph[0][2] = 4;
    graph[0][4] = 3;
    graph[2][3] = 1;

    pair<int**, int**> myPair = floydMarshall(graph, 4);
    int** dist = myPair.first;
    cout << "dist no.0 to no.3:  " << dist[0][3] << endl;
    cout << "dist no.0 to no.2:  " << dist[0][2] << endl;
    cout << "dist no.1 to no.2:  " << dist[1][2] << endl;

    freeArray(graph, 4);
    freeArray(myPair.first, 4);
    freeArray(myPair.second, 4);
    return 0;
}