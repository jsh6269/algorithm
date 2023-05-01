#include <iostream>
#include <stack>
using namespace std;
int n;

int* StackStockSpan(int* quotes){
//    complexity: O(n)
    int* spans = (int*)malloc(sizeof(int) * n);
    stack<int> S;

    spans[0] = 1;
    S.push(0);

    for(int i=1; i<n; i++){
        while(!S.empty() && quotes[S.top()] <= quotes[i]){
            S.pop();
        }
        if(S.empty()){
            spans[i] = i + 1;
        }
        else{
            spans[i] = i - S.top();
        }
        S.push(i);
    }
    return spans;
}

int main(){
    int example[7] = {7, 11, 8, 6, 3, 8, 9};
    n = sizeof(example) / sizeof(example[0]);
    int* res = StackStockSpan(example);
    for(int i=0; i<n; i++){
        cout << res[i] << " ";
    }
    free(res);
    return 0;
}