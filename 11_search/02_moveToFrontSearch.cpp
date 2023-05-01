#include <iostream>
#include <list>
using namespace std;

int moveToFrontSearch(list<int>* L, int item){
    int cnt = 0;
    for(auto iter = L->begin(); iter != L->end(); iter++){
        if(*iter == item){
            if(iter != L->begin()){
                L->erase(iter);
                L->push_front(item);
            }
            return cnt;
        }
        cnt++;
    }
    return -1;
}

int main(){
    list<int> example;
    int ex[6] = {3,1,2,4,5,6};
    example.assign(ex, ex+6);

    int ans1 = moveToFrontSearch(&example, 4);
    cout << ans1 << endl;
    int ans2 = moveToFrontSearch(&example, 4);
    cout << ans2 << endl;
    int ans3 = moveToFrontSearch(&example, 6);
    cout << ans3 << endl;
    int ans4 = moveToFrontSearch(&example, 4);
    cout << ans4 << endl;
    return 0;
}