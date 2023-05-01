#include <iostream>
#include <cmath>
using namespace std;

int binarySearch(const int A[], int n, int item){
    // time complexity: O(logn)
    int low = 0;
    int high = n;
    while(low <= high){
        int m = low + (int)floor((high - low) / 2);
        if(A[m] < item){
            low = m + 1;
        }
        else if(item < A[m]){
            high = m - 1;
        }
        else{
            return m;
        }
    }
    return -1;
}

int main(){
    int A[12] = {1, 3, 4, 5, 7, 10, 14, 16, 19, 20,35, 67};
    cout << binarySearch(A, 12, 20) << endl;
    cout << binarySearch(A, 12, 2);
    return 0;
}