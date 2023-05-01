#include <iostream>
using namespace std;
int cnt = 0;

long long fibonacci_recursive(int n, long long* dy){
    // time complexity: O(n)
    cnt++;
    if(n < 2){
        return n;
    }
    if(dy[n] != 0){
        return dy[n];
    }
    dy[n] = fibonacci_recursive(n-1, dy) + fibonacci_recursive(n-2, dy);
    return dy[n];
}

long long fibonacci_loop(int n){
    if(n < 2){
        return n;
    }
    long long pre = 0, cur = 1;
    for(int i=0; i<n-1; i++){
        long long temp = pre + cur;
        pre = cur;
        cur = temp;
    }
    return cur;
}

int main(){
    auto* dy = (long long*) malloc(sizeof(long long) * 100);
    fill_n(dy, 100, 0);
    dy[0] = 0, dy[1] = 1;
    cout << fibonacci_recursive(52, dy) << endl;
    cout << "total function call: " << cnt << endl;
    cout << fibonacci_loop(52) << endl;
    free(dy);
    return 0;
}