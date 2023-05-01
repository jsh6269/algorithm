#include <iostream>
#include <list>
using namespace std;

int transpositionSearch(list<int>* L, int item){
    int cnt = 0;
    list<int>::iterator pre;
    for(auto iter = L->begin(); iter != L->end(); iter++){
        if(*iter == item){
            if(iter != L->begin()){
                iter_swap(pre, iter);
            }
            return cnt;
        }
        cnt++;
        pre = iter;
    }
    return -1;
}

int main(){
    list<int> example;
    int ex[6] = {3,1,2,4,5,6};
    example.assign(ex, ex+6);

    int ans1 = transpositionSearch(&example, 4);
    cout << ans1 << endl;
    int ans2 = transpositionSearch(&example, 4);
    cout << ans2 << endl;
    int ans3 = transpositionSearch(&example, 6);
    cout << ans3 << endl;
    int ans4 = transpositionSearch(&example, 4);
    cout << ans4 << endl;
    int ans5 = transpositionSearch(&example, 4);
    cout << ans5 << endl;
    int ans6 = transpositionSearch(&example, 4);
    cout << ans6 << endl;
    return 0;
}