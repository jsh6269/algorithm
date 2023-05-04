#include <iostream>
using namespace std;

int sequentialSearch(const int A[], int n, int item){
    for(int i=0; i<n; i++){
        if(A[i] == item){
            return i;
        }
    }
    return -1;
}

int main(){
    int example[6] = {3,1,2,4,5,6};
    int ans = sequentialSearch(example, 6, 4);
    cout << ans << endl;
    return 0;
}