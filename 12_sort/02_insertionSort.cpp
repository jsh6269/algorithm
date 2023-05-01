#include <iostream>
using namespace std;

void insertionSort(int* A, int n){
    // time complexity: O(n^2)
    for(int i=1; i<n; i++){
        int j = i;
        while(j > 0 && A[j-1] > A[j]){
            swap(A[j-1], A[j]);
            j--;
        }
    }
}

int main(){
    int A[10] = {4, 2, 1, 3, 5, 6, 7, 1, 9, 8};
    insertionSort(A, 10);
    for(int val : A){
        cout << val << " ";
    }
    return 0;
}