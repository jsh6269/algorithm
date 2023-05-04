#include <iostream>
#include <list>
using namespace std;

pair<int, list<int>> exchange(int* coins, int n_coins, int amount){
    // time complexity: O(n_coins * amount)
    int dy[amount+1];
    int path[amount+1];
    fill_n(dy, amount+1, 999);
    fill_n(path, amount+1, -1);
    dy[0] = 0;
    for(int i=0; i<n_coins; i++){
        for(int j=coins[i]; j<=amount; j++)
            if(dy[j] >= dy[j-coins[i]] + 1){
                dy[j] = dy[j-coins[i]] + 1;
                path[j] = i;
            }
    }
    list<int> coinLst;
    int pos = amount;
    while(path[pos] != -1){
        int coin = coins[path[pos]];
        coinLst.push_back(coin);
        pos -= coin;
    }
    return make_pair(dy[amount], coinLst);
}

int main(){
    int coins[4] = {1, 7, 10, 11};
    int amount = 27;
    pair<int, list<int>> ans = exchange(coins, 4, amount);
    cout << ans.first << endl;
    for(int coin : ans.second){
        cout << coin << " ";
    }
    return 0;
}