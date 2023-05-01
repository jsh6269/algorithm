#include <iostream>
using namespace std;
int partition(int*, int, int);

void quickSort(int* A, int low, int high){
    // time complexity: average O(nlogn), worst O(n^2)
    if(low < high){
        int pivot = partition(A, low, high);
        quickSort(A, low, pivot-1);
        quickSort(A, pivot+1, high);
    }
}

int partition(int* A, int low, int high){
    int pivot = (rand() % (high-low+1)) + low;
    swap(A[pivot], A[high]);
    int b = low;
    for(int i=low; i<high; i++){
        if(A[i] < A[high]){
            swap(A[i], A[b]);
            b++;
        }
    }
    swap(A[high], A[b]);
    return b;
}

int main(){
    int A[10] = {4, 2, 1, 3, 5, 6, 7, 1, 9, 8};
    srand(time(NULL));
    quickSort(A, 0, 9);
    for(int val : A){
        cout << val << " ";
    }
    return 0;
}