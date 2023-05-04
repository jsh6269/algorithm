#include <iostream>
using namespace std;

void bubbleSort(int* A, int n){
    // time complexity: O(n^2)
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(A[j] > A[j+1]){
                swap(A[j], A[j+1]);
            }
        }
    }
}

int main(){
    int A[10] = {4, 2, 1, 3, 5, 6, 7, 1, 9, 8};
    bubbleSort(A, 10);
    for(int val : A){
        cout << val << " ";
    }
    return 0;
}