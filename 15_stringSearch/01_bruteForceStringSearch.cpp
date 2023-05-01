#include <iostream>
#include <queue>
using namespace std;

queue<int> bruteForceStringSearch(string pattern, string text){
    // time complexity: O(mn)
    queue<int> q;
    int m = (int)pattern.length();
    int n = (int)text.length();
    for(int i=0; i<n-m; i++){
        int j = 0;
        while(j < m && pattern[j] == text[i+j]){
            j++;
        }
        if(j == m){
            q.push(i);
        }
    }
    return q;
}

int main(){
    queue<int> q = bruteForceStringSearch("is", "this is good!");
    while(!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}