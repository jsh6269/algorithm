#include <iostream>
using namespace std;

void selectionSort(int* A, int n){
    // time complexity: O(n^2)
    for(int i=0; i<n-1; i++){
        int minID = i;
        for(int j=i+1; j<n; j++){
            if(A[j] < A[minID]){
                minID = j;
            }
        }
        if(i != minID){
            swap(A[i], A[minID]);
        }
    }
}

int main(){
    int A[10] = {4, 2, 1, 3, 5, 6, 7, 1, 9, 8};
    selectionSort(A, 10);
    for(int val : A){
        cout << val << " ";
    }
    return 0;
}