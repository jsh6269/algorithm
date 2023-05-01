#include <iostream>
using namespace std;

void sieveEratosthenes(int n){
    // time complexity: O(nloglogn)
    int isPrime[n+1];
    fill_n(isPrime, n+1, true);
    isPrime[0] = false;
    isPrime[1] = false;

    int p = 2;
    while(p * p <= n){
        if(isPrime[p]){
            int j = p;
            while(j * p <= n){
                isPrime[j * p] = false;
                j++;
            }
        }
        p++;
    }
    int cnt = 0;
    for(int i=0; i<n; i++){
        if(isPrime[i]){
            cout << i << " ";
            cnt++;
        }
    }
    cout << endl << "totNum: " << cnt;
}

int main(){
    // 168개
    sieveEratosthenes(1000);
    return 0;
}