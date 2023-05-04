#include <iostream>
#include <queue>
using namespace std;
int* findBorders(string);

queue<int> knuthMorrisPratt(string pattern, string text){
    queue<int> q;
    int m = (int)pattern.length();
    int n = (int)text.length();
    int* border = findBorders(pattern);
    int j = 0;

    for(int i=0; i<n; i++){
        while(j>0 && pattern[j] != text[i]){
            j = border[j];
        }
        if(pattern[j] == text[i]){
            j++;
        }
        if(j == m){
            q.push(i-j+1);
            j = border[j];
        }
    }
    free(border);
    return q;
}

int* findBorders(string pattern){
    int m = (int)pattern.length();
    int* border = (int*) malloc(sizeof(int) * (m+1));
    int j = 0;
    border[0] = j;
    border[1] = j;
    for(int i=1; i<m; i++){
        while(j>0 && pattern[j] != pattern[i]){
            j = border[j];
        }
        if(pattern[j] == pattern[i]){
            j++;
        }
        border[i+1] = j;
    }
    return border;
}

int main(){
    queue<int> q = knuthMorrisPratt("is", "this is good!");
    while(!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}