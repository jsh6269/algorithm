#include <iostream>
#include <list>
#include <tuple>
using namespace std;

int** create2DArray(int height, int width=-1, int init=-1){
    int **arr;
    width = (width == -1) ? height : width;
    arr = (int**) malloc ( sizeof(int*) * height);
    for(int i=0; i<height; i++){
        arr[i] = (int*) malloc ( sizeof(int) * width);
        for(int j=0; j<width; j++){
            arr[i][j] = init;
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

tuple<int, int, int, list<char>> knapsack(char* name, int* weight, int* value, int n, int storage){
    // time complexity: O(n * storage)
    // can pick only one item from one kind
    int** dy = create2DArray(n, storage+1, 0);
    int** isPicked = create2DArray(n, storage+1, 0);

    for(int i=0; i<n; i++){
        for(int j=0; j<=storage; j++){
            if(i == 0){
                // if i == 0, we cannot access to dy[i-1][?]
                if(j >= weight[0]){
                    // if item i storable, pick it
                    dy[i][j] = value[i];
                    isPicked[i][j] = 1;
                }
            }
            else if(j >= weight[i] && dy[i-1][j] < dy[i-1][j-weight[i]] + value[i]){
                // if we can store item i && it's better to do that
                dy[i][j] = dy[i-1][j-weight[i]] + value[i];
                isPicked[i][j] = 1;
            }
            else{
                // we do not store item i
                dy[i][j] = dy[i-1][j];
                isPicked[i][j] = 0;
            }
        }
    }
    list<char> track;
    // note that last item's id is n-1 (not n)
    int totalValue = dy[n-1][storage];
    int pos = n-1;
    int totalNum = 0, totalWeight = 0;

    while(pos != -1){
        if(isPicked[pos][storage-totalWeight] == 1){
            totalNum++;
            totalWeight += weight[pos];
            track.push_front(name[pos]);
        }
        pos--;
    }
    freeArray(dy, n);
    freeArray(isPicked, n);
    return make_tuple(totalValue, totalNum, totalWeight, track);
}

int main(){
    char name[5] = {'A','B','C','D','E'};
    int weight[5] = {2, 3, 4, 5, 7};
    int value[5] = {2, 4, 7, 8, 12};
    tuple<int, int, int, list<char>> ans = knapsack(name, weight, value, 5, 15);
    cout << "total value: " << get<0>(ans) << endl;
    cout << "total number: " << get<1>(ans) << endl;
    cout << "total weight: " << get<2>(ans) << endl;
    for(char name : get<3>(ans)){
        cout << name << " ";
    }
    return 0;
}
