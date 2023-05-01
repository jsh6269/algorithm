#include <iostream>
using namespace std;

void push(int* H, int item, int* s){
    int k = *s;
    H[*s] = item;
    *s = *s + 1;
    while(k > 0){
        int parent = (k-1)/2;
        if(H[parent] > H[k]){
            swap(H[parent], H[k]);
            k = parent;
        }
        else{
            break;
        }
    }
}
int pop(int* H, int* s){
    int k = 1;
    swap(H[0], H[*s-1]);
    *s = *s - 1;
    while(k < *s){
        int parent = (k-1)/2;
        if(k+1 < *s && H[k] > H[k+1]){
            k++;
        }
        if(H[parent] > H[k]){
            swap(H[parent], H[k]);
            k = 2 * k + 1;
        }
        else{
            break;
        }
    }
    return H[*s];
}

void printBinaryTree(int* H, int* s){
    int cnt = 0;
    int temp = 2;
    for(int i=0; i<*s; i++){
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
    int H[1000], s=0;
    push(H, 5, &s);
    push(H, 9, &s);
    push(H, 4, &s);
    push(H, 3, &s);
    push(H, 2, &s);
    push(H, 1, &s);
    push(H, 8, &s);
    push(H, 1, &s);
    printBinaryTree(H, &s);
    int a = pop(H, &s);
    cout << "popped value: " << a << endl;
    printBinaryTree(H, &s);
    a = pop(H, &s);
    cout << "popped value: " << a << endl;
    printBinaryTree(H, &s);
    a = pop(H, &s);
    cout << "popped value: " << a << endl;
    printBinaryTree(H, &s);
    return 0;
}