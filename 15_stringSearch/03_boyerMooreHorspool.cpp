#include <iostream>
#include <queue>
using namespace std;
int* createRtOccurrencesTable(string, int);

queue<int> boyerMooreHorspool(string pattern, string text, int s=128){
    // time complexity: worst O(mn), average O(n/m)
    queue<int> q;
    int m = (int)pattern.length();
    int n = (int)text.length();
    int* shiftTable = createRtOccurrencesTable(pattern, s);
    int i = 0;
    while(i <= n-m){
        int j = m-1;
        while(j>=0 && text[i+j] == pattern[j]){
            j--;
        }
        if(j < 0){
            q.push(i);
        }
        i += shiftTable[(int)text[i+m-1]];
    }
    free(shiftTable);
    return q;
}

int* createRtOccurrencesTable(string pattern, int s){
    // time complexity: O(m+s)
    int* rsTable = (int*) malloc(sizeof(int) * s);
    int m = (int)pattern.length();
    for(int i=0; i<s; i++){
        rsTable[i] = m;
    }
    for(int i=0; i<m-1; i++){
        rsTable[(int)pattern[i]] = m-i-1;
    }
    return rsTable;
}

int main(){
    queue<int> q = boyerMooreHorspool("is", "this is good!");
    while(!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}