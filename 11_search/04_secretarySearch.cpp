#include <iostream>
#include <cmath>
using namespace std;

int secretarySearch(const int A[], int n){
    // time complexity: O(n)
    int m = (int) ceil(n / M_E);
    int c = 0;
    for(int i=1; i<m; i++){
        if(A[i] > A[c]){
            c = i;
        }
    }
    for(int i=m; i<n; i++){
        if(A[i] > A[c]){
            return i;
        }
    }
    return -1;
}

int main(){
    int A[10] = {5, 2, 1, 4, 2, 1, 7, 2, 3, 4};
    int ans = secretarySearch(A, 10);
    cout << ans << "th value: " << A[ans];
    return 0;
}