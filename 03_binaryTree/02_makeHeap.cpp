#include <iostream>
using namespace std;

void sink(int* A, int i, int n){
    int parent = i;
    int k = 2*i + 1;
    while(k < n){
        if(k < n-1 && A[k] > A[k+1]){
            k++;
        }
        if(A[parent] > A[k]){
            swap(A[parent], A[k]);
            parent = k;
            k = 2*parent + 1;
        }
        else{
            break;
        }
    }
}
void makeHeap(int* A, int n){
    for(int i=(n-1)/2; i>=0; i--){
        sink(A, i, n);
    }
}
void printBinaryTree(int* H, int n){
    int cnt = 0;
    int temp = 2;
    for(int i=0; i<n; i++){
        cout << H[i] << " ";
        if(i == cnt){
            cout << endl;
            cnt += temp;
            temp *= 2;
        }
    }
    cout << endl << endl;
}

int main(){
    int A[8] = {5,9,4,3,2,1,8,1};
    makeHeap(A, 8);
    printBinaryTree(A, 8);
    return 0;
}