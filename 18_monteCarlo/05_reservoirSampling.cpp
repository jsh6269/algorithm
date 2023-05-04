#include <iostream>
#include <cmath>
#include <random>
#include <queue>
using namespace std;

int* reservoirSampling(queue<int> src, int m){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> rand(0, 1);

    int* S = (int*) malloc(sizeof(int) * m);
    for(int i=0; i<m; i++){
        S[i] = src.front();
        src.pop();
    }
    int t = m;
    while(!src.empty()){
        t++;
        int u = floor(rand(gen) * t + 1);
        if(u <= m){
            S[u - 1] = src.front();
        }
        src.pop();
    }
    return S;
}

int main(){
    int example[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11};
    queue<int> q;
    for(int val : example){
        q.push(val);
    }

    int testNum[12];
    fill_n(testNum, 12, 0);
    for(int rep=0; rep<100000; rep++){
        int* ans = reservoirSampling(q, 5);
        for(int i=0; i<5; i++){
            if(rep < 10)
                cout << ans[i] << " ";
            testNum[ans[i]]++;
        }
        if(rep < 10)
            cout << endl;
        free(ans);
    }
    cout << "count value:" << endl;
    for(int val : testNum){
        cout << val << " ";
    }
}


