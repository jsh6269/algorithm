#include <iostream>
#include <list>
#include <tuple>
using namespace std;

tuple<int, int, int, list<char>> knapsack(char* name, int* weight, int* value, int n, int storage){
    // time complexity: O(n * storage)
    // can pick several items from one kind
    int* dy = (int*) malloc(sizeof(int) * (storage+1));
    int* path = (int*) malloc(sizeof(int) * (storage+1));
    fill_n(dy, storage+1, 0);
    fill_n(path, storage+1, -1);

    for(int i=0; i<n; i++){
        for(int j=weight[i]; j<=storage; j++){
            if(dy[j] < dy[j-weight[i]] + value[i]){
                dy[j] = dy[j-weight[i]] + value[i];
                path[j] = i;
            }
        }
    }
    list<char> track;
    int totalValue = dy[storage];
    int pos = storage;
    int totalNum = 0, totalWeight = 0;
    while(path[pos] != -1){
        totalNum++;
        track.push_front(name[path[pos]]);
        totalWeight += weight[path[pos]];
        pos = pos - weight[path[pos]];
    }
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
