#include <iostream>
using namespace std;
int n;
int* SimpleStockSpan(int* quotes){
//    complexity: O(n^2)
    int* spans = (int*)malloc(sizeof(int) * n);
    bool span_end = false;
    for(int i=0; i<n; i++){
        int k = 1;
        span_end = false;
        while(i - k >= 0 && !span_end){
            if(quotes[i-k] <= quotes[i])
                k++;
            else
                span_end = true;
        }
        spans[i] = k;
    }
    return spans;
}

int main(){
    int example[7] = {7, 11, 8, 6, 3, 8, 9};
    n = sizeof(example) / sizeof(example[0]);
    int* res = SimpleStockSpan(example);
    for(int i=0; i<n; i++){
        cout << res[i] << " ";
    }
    free(res);
    return 0;
}