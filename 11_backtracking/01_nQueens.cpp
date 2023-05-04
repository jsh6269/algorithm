#include <iostream>
#include <list>
using namespace std;
list<int> ans[100];

bool promise(int i, int* col){
    for(int r=1; r<i; r++){
        if(col[r] == col[i]){
            return false;
        }
        if(abs(col[r]-col[i]) == abs(r-i)){
            return false;
        }
    }
    return true;

}

int queens(int i, int n){
    static int col[100];
    static int cnt;

    if(promise(i, col)){
        if(i == n){
            for(int r=1; r<=n; r++){
                cout << col[r] << " ";
                ans[cnt].push_back(col[r]);
            }
            cnt++;
            cout << endl;
        }
        else{
            for(int j=1; j<=n; j++){
                col[i+1] = j;
                queens(i+1, n);
            }
        }
    }
    return cnt;
}

void showGrid(const list<int>& pos, int n){
    for(int idx : pos){
        for(int j=1; j<=n; j++){
            if(idx == j){
                cout << "* ";
            }
            else{
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    int num = queens(0, 8);
    cout << endl;
    cout << num << " found" << endl;
    showGrid(ans[3], 8);
    showGrid(ans[5], 8);
    return 0;
}