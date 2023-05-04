#include <iostream>
#include <utility>
using namespace std;
void track(int**, int, int);

int** create2DArray(int height, int width=-1, int value=-1){
    int **arr;
    width = (width == -1) ? height : width;
    arr = (int**) malloc ( sizeof(int*) * height);
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

int optimalOrder(pair<int, int>* matrices, int n){
    // time complexity: O(n^3)
    int dy[n][n];
    int** path = create2DArray(n, n, -1);
    fill(dy[0], dy[0]+n*n, 99999);

    for(int i=0; i<n; i++){
        for(int j=0; j<n-i; j++){
            int begin = j, end = j+i;
            if(begin == end){
                dy[begin][end] = 0;
                continue;
            }
            for(int k=begin; k<end; k++){
                int alter = dy[begin][k] + dy[k+1][end] + matrices[begin].first * matrices[k].second * matrices[end].second;
                if(dy[begin][end] > alter){
                    dy[begin][end] = alter;
                    path[begin][end] = k;
                }
            }
        }
    }
    track(path, 0, n-1);
    cout << endl;
    freeArray(path, n);
    return dy[0][n-1];
}

void track(int** path, int begin, int end){
    if(begin == end){
        cout << (char)(begin + 65);
        return;
    }
    if(begin + 1 == end){
        cout << (char)(begin + 65) << (char)(end + 65);
        return;
    }
    int inter = path[begin][end];
    cout << (begin == inter ? "" : "(");
    track(path, begin, inter);
    cout << (begin == inter ? "" : ")") << (inter+1 == end ? "" : "(");
    track(path, inter+1, end);
    cout << (inter+1 == end ? "" : ")");
}

int main(){
    pair<int, int> matrices[5] = {make_pair(4,3),make_pair(3,2),make_pair(2,5),
                                  make_pair(5,1),make_pair(1,3)};
    cout << optimalOrder(matrices, 5);
    return 0;
}
