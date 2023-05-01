#include <iostream>
#include <queue>
using namespace std;

void preorder(int* H, int *s, int i){
    if(i < *s){
        cout << H[i] << " ";
        preorder(H, s, 2*i+1);
        preorder(H, s, 2*i+2);
    }
}
void inorder(int* H, int *s, int i){
    if(i < *s){
        inorder(H, s, 2*i+1);
        cout << H[i] << " ";
        inorder(H, s, 2*i+2);
    }
}
void postorder(int* H, int *s, int i){
    if(i < *s){
        postorder(H, s, 2*i+1);
        postorder(H, s, 2*i+2);
        cout << H[i] << " ";
    }
}
void levelorder(int* H, int *s, int i){
    if(*s == 0){
        return;
    }
    queue<int> q;
    q.push(i);
    while(!q.empty()){
        int top = q.front();
        q.pop();
        cout << H[top] << " ";
        if(2 * top + 1 < *s){
            q.push(2 * top + 1);
        }
        if(2 * top + 2 < *s){
            q.push(2 * top + 2);
        }
    }
}
int main(){
    int H[8] = {1, 2, 1, 3, 5, 4, 8, 9};
    int s = 8;
    cout << "original tree" << endl;
    for(int i=0; i<s; i++){
        cout << H[i] << " ";
    }
    cout << endl;
    cout << "preorder traverse" << endl;
    preorder(H, &s, 0);
    cout << endl;
    cout << "inorder traverse" << endl;
    inorder(H, &s, 0);
    cout << endl;
    cout << "postorder traverse" << endl;
    postorder(H, &s, 0);
    cout << endl;
    cout << "levelorder traverse" << endl;
    levelorder(H, &s, 0);
    cout << endl;
    return 0;
}