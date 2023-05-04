#include <iostream>
#include <queue>
using namespace std;

int josephus(int n, int hop){
    // time complexity: O(n*hop)
    queue<int> q;
    for(int i=0; i<n; i++){
        q.push(i);
    }
    while(q.size() != 1){
        q.pop();
        for(int i=0; i<hop; i++){
            q.push(q.front());
            q.pop();
        }
    }
    return q.front();
}
int main(){
    cout << josephus(10, 3) << endl;
    cout << josephus(12, 0) << endl;
    cout << josephus(1, 3) << endl;
    cout << josephus(13, 5) << endl;
    return 0;
}