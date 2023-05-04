#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

pair<int, list<int>> kadane(int* arr, int n){
    // time complexity: O(n)
    // finding a contiguous subarray which has maximum sum
    int dy[n];
    for(int i=0; i<n; i++){
        if(i == 0)
            dy[i] = arr[i];
        else
            dy[i] = max(arr[i], dy[i-1] + arr[i]);
    }
    list<int> track;
    int* id = max_element(dy, dy+n);
    int sum = *id;
    int cnt = 0;
    while(cnt != sum){
        track.push_front(arr[id-dy]);
        cnt += arr[id-dy];
        id--;
    }
    return make_pair(sum, track);
}

int main(){
    int test[7] = {1,-2,3,5,-4,2,5};
    pair<int, list<int>> ans = kadane(test, 7);
    cout << ans.first << ": ";
    for(int val : ans.second){
        cout << val << " ";
    }
}