#include <iostream>
#include <cmath>
using namespace std;

void arrayMergeInPlace(int* A, int l, int m, int h){
    // A[1], ... , A[m]  |  A[m+1], ... , A[h]
    int temp[h-l+1];
    for(int k=l; k<h+1; k++){
        temp[k-l] = A[k];
    }
    int i=0;
    int tm = m - l + 1;
    int th = h - l + 1;
    int j = tm;

    for(int k=l; k<h+1; k++){
        if(i >= tm){
            A[k] = temp[j++];
        }
        else if(j >= th){
            A[k] = temp[i++];
        }
        else if(temp[i] <= temp[j]){
            A[k] = temp[i++];
        }
        else{
            A[k] = temp[j++];
        }
    }
}

void mergeSort(int* A, int l, int h){
    // time complexity: O(nlogn)
    if(l < h){
        int m = l + (int)floor((h-l)/2);
        mergeSort(A, l, m);
        mergeSort(A, m+1, h);
        arrayMergeInPlace(A, l, m, h);
    }
}

int main(){
    int A[10] = {4, 2, 1, 3, 5, 6, 7, 1, 9, 8};
    mergeSort(A, 0, 9);
    for(int val : A){
        cout << val << " ";
    }
    return 0;
}