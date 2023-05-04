#include <iostream>
#include <list>
using namespace std;

bool** create2DArray(int height, int width=-1, bool value=false){
    bool **arr;
    width = (width == -1) ? height : width;
    arr = (bool**) malloc ( sizeof(bool*) * height);
    for(int i=0; i<height; i++){
        arr[i] = (bool*) malloc ( sizeof(bool) * width);
        for(int j=0; j<width; j++){
            arr[i][j] = value;
        }
    }
    return arr;
}

void freeArray(bool **arr, int height){
    for(int i=0; i<height; i++){
        free(arr[i]);
    }
    free(arr);
}

bool promise(int i, bool** graph, const int* color){
    for(int j=0; j<i; j++){
        if(graph[i][j] && color[i] == color[j]){
            return false;
        }
    }
    return true;
}

void coloring(int i, int n, int m, bool** graph, list<int*>* ans){
    // n: number of area, m: number of color
    static int color[100];
    if(i == n){
        int* colored = (int*) malloc(sizeof(int) * n);
        memcpy(colored, color, n * sizeof(int));
        ans->push_back(colored);
        return;
    }
    for(int c=0; c<m; c++){
        color[i] = c;
        if(promise(i, graph, color)) {
            coloring(i + 1, n, m, graph, ans);
        }
        color[i] = -1;
    }
}

int main(){
    int n = 4, m = 3;
    bool** graph = create2DArray(n, n);
    graph[0][2] = graph[2][0] = true;
    graph[0][1] = graph[1][0] = true;
    graph[1][2] = graph[2][1] = true;
    graph[0][3] = graph[3][0] = true;
    graph[2][3] = graph[3][2] = true;

    list<int*> ans;
    coloring(0, n, m, graph, &ans);

    for(int* caseOne : ans){
        for(int i=0; i<n; i++){
            cout << caseOne[i] << " ";
        }
        cout << endl;
    }
    freeArray(graph, n);
    return 0;
}