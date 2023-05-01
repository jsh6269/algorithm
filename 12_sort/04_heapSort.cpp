#include <iostream>
#include <cmath>
using namespace std;

void sink(int* A, int i, int n){
    int k = i;
    bool placed = false;
    int j = 2*k + 1;
    while(!placed && j < n){
        if(j < n-1 && A[j] < A[j+1]){
            j++;
        }
        if(A[k] >= A[j]){
            placed = true;
        }
        else{
            swap(A[k], A[j]);
        }
        k = j;
        j = 2*k + 1;
    }
}
void heapSort(int* A, int n){
    // time complexity: O(nlogn)
    for(int i=floor((n-1)/2); i>=0; i--){
        sink(A, i, n);
    }
    while(n > 0){
        swap(A[0], A[n-1]);
        n--;
        sink(A, 0, n);
    }
}

int main(){
    int A[10] = {4, 2, 1, 3, 5, 6, 7, 1, 9, 8};
    heapSort(A, 10);
    for(int val : A){
        cout << val << " ";
    }
    return 0;
}