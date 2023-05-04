#include <iostream>
#include <list>
using namespace std;

pair<int, list<int>> find_lis(const int* seq, int n){
    int* dy = (int*) malloc(sizeof(int) * n);
    int* path = (int*) malloc(sizeof(int) * n);
    fill_n(dy, n, 1);
    fill_n(path, n, -1);
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            if(seq[j] < seq[i] && dy[j] + 1 > dy[i]){
                dy[i] = dy[j] + 1;
                path[i] = j;
            }
        }
    }
    int max = 0, id = 0;
    for(int i=0; i<n; i++){
        if(dy[i] > max){
            max = dy[i];
            id = i;
        }
    }

    list<int> track;
    track.push_front(id);
    while(path[id] != -1){
        id = path[id];
        track.push_front(id);
    }
    free(dy);
    free(path);
    return make_pair(max, track);
}

int main(){
    int seq[9] = {11, 17, 5, 8, 6, 4, 7, 12,3};
    pair<int, list<int>> ans = find_lis(seq, 9);
    cout << ans.first << endl;
    for(int item : ans.second){
        cout << seq[item] << " ";
    }
}