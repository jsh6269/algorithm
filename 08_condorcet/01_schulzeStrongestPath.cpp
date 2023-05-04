#include <iostream>
#include <utility>
#include <list>
#include <vector>
using namespace std;

// total time complexity: O(|C|^3+|B||C|^2)
// |B| = number of ballots
// |C| = number of candidates

int** create2DArray(int height, int width=-1){
    int **arr;
    width = (width == -1) ? height : width;
    arr = (int**) malloc ( sizeof(int*) * height);
    for(int i=0; i<height; i++){
        arr[i] = (int*) malloc ( sizeof(int) * width);
    }
    return arr;
}

void freeArray(int **arr, int height){
    for(int i=0; i<height; i++){
        free(arr[i]);
    }
    free(arr);
}

int** calcPairwisePreferences(const int* ballots, int num_vote, int num_candidate){
    int** pref;
    pref = create2DArray(num_candidate);
    for(int i=0; i<num_candidate; i++){
        for(int j=0; j<num_candidate; j++){
            pref[i][j] = 0;
        }
    }
    for(int i=0; i<num_vote; i++){
        for(int j=0; j<num_candidate; j++){
            for(int k=j+1; k<num_candidate; k++){
                pref[ballots[i * num_candidate + j]][ballots[i * num_candidate + k]]++;
            }
        }
    }
    return pref;
}

void setVotesByType(int votes[][4], int types[][4], int start, int type, int rep){
    for(int i=start; i<start+rep; i++){
        for(int j=0; j<4; j++){
            votes[i][j] = types[type][j];
        }
    }
}

pair<int**, int**> calcStrongestPaths(int** W, int n){
    int **S;
    int **pred;
    S = create2DArray(n);
    pred = create2DArray(n);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(W[i][j] > W[j][i]){
                S[i][j] = W[i][j] - W[j][i];
                pred[i][j] = i;
            }
            else{
                S[i][j] = -999;
                pred[i][j] = -1;
            }
        }
    }

    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            if(i != k){
                for(int j=0; j<n; j++){
                    if(j != i && S[i][j] < min(S[i][k], S[k][j])){
                        S[i][j] = min(S[i][k], S[k][j]);
                        pred[i][j] = pred[k][j];
                    }
                }
            }
        }
    }
    return make_pair(S, pred);
}

vector<list<int>> calcResults(int** S, int n){
    vector<list<int>> wins(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i != j && S[i][j] > S[j][i]){
                wins[i].push_back(j);
            }
        }
    }
    return wins;
}

int main(){
    int **pref;
    int ballots[21][4];
    int types[5][4] = {{0,2,3,1},{1,0,3,2},{2,3,1,0},
                    {3,1,0,2},{3,2,1,0}};

    setVotesByType(ballots, types, 0, 0, 6);
    setVotesByType(ballots, types, 6, 1, 4);
    setVotesByType(ballots, types, 10, 2, 3);
    setVotesByType(ballots, types, 13, 3, 4);
    setVotesByType(ballots, types, 17, 4, 4);

    // |B| = number of ballots
    // |C| = number of candidates
    // "calcPairwisePreferences" time complexity: O(|C|^2+|B||C|^2)
    pref = calcPairwisePreferences(*ballots, 21, 4);
    // "calcStrongestPaths" time complexity: O(|C|^3)
    pair<int**, int**> myPair = calcStrongestPaths(pref, 4);
    int** S = myPair.first;
    // "calcResults" time complexity: O(|C|^2)
    vector<list<int>> wins = calcResults(S, 4);

    for(int i=0; i<4; i++){
        cout << "no." << i << " wins: ";
        for(int val : wins[i]){
            cout << val << " ";
        }
        cout << endl;
    }
    freeArray(pref, 4);
    return 0;
}