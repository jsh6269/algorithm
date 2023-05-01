#include <iostream>
#include <random>
#include <list>
using namespace std;

list<int> randomSubset(int n, int exception=-1){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> rand(0, 1);

    list<int> subset;
    for(int i=0; i<n; i++){
        if(i != exception && rand(gen) < 0.5){
            subset.push_back(i);
        }
    }
    return subset;
}

float* banzhafMeasure(string* voter, const int* votes, int n, int q, int rep){
    int cnt, numSwing;
    int voteSum;
    auto* banzhaf = (float*) malloc(sizeof(float) * n);
    for(int i=0; i<n; i++){
        cnt = 0, numSwing = 0;
        while(cnt < rep){
            list<int> coalitionID = randomSubset(n, i);
            voteSum = 0;
            for(int idx : coalitionID){
                voteSum += votes[idx];
            }
            if(voteSum < q && voteSum + votes[i] >= q){
                numSwing++;
            }
            cnt++;
        }
        banzhaf[i] = (float)numSwing / (float)cnt;
        cout << voter[i] << ": " << banzhaf[i] << endl;
    }
    return banzhaf;
}

int main(){
    int q = 6;
    string voter[4] = {"A", "B", "C", "D"};
    int votes[4] = {4, 2, 1, 3};
    banzhafMeasure(voter, votes, 4, q, 10000);
    cout << "actual value: 0.625, 0.375, 0.125, 0.375";
}


