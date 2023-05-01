#include <iostream>
#include <cmath>
#include <random>
using namespace std;

int* selectionSampling(const int* P, int n, int m){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> rand(0, 1);

    int* S = (int*) malloc(sizeof(int) * m);
    int k = 0, t = 0;
    while (k < m){
        if(rand(gen) * (n-t) < m-k){
            S[k] = P[t];
            k++;
        }
        t++;
    }
    return S;
}

int main(){
    int example[12] = {5, 24, 31, 4, 12, 6, 7, 8, 2, 34, 14,1};
    for(int rep=0; rep< 10; rep++){
        int* ans = selectionSampling(example, 12, 5);
        for(int i=0; i<5; i++){
            cout << ans[i] << " ";
        }
        cout << endl;
        free(ans);
    }
}


