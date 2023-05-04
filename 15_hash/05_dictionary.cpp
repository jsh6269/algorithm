#include <iostream>
#include <list>
using namespace std;
list<pair<int, string>> nation[23];

int integerHash(int k, int m){
    return k % m;
}

void insertByHash(int key, const string& value){
    // time complexity: O(1)
    int hash = integerHash(key, 23);
    nation[hash].emplace_back(key, value);
}

bool searchByHash(int key, const string& value){
    // time complexity: O(n/m)
    // n: number of keys, m: size of hash table
    int hash = integerHash(key, 23);
    for(const auto& item : nation[hash]){
        if(item.first == key && item.second == value){
            return true;
        }
    }
    return false;
}

pair<int, string> removeByHash(int key, const string& value){
    // time complexity: O(n/m)
    // n: number of keys, m: size of hash table
    int hash = integerHash(key, 23);
    for(auto iter = nation[hash].begin(); iter!=nation[hash].end(); iter++){
        if(iter->first == key && iter->second == value){
            pair<int, string> erased = make_pair(iter->first, iter->second);
            nation[hash].erase(iter);
            return  erased;
        }
    }
    return make_pair(-1, nullptr);
}

void echo(const pair<int, string>& ex, const string& alert){
    cout << ex.first << ", " << ex.second << alert << endl;
}

int main(){
    string name[17] = {"China","India","USA","Indonesia","Brazil", "Pakistan","Nigeria",
                       "Bangladesh","Russia","Japan","Mexico","Philippines","Vietnam",
                       "Ethiopia","Egypt","Germany","Iran"};
    int code[17] = {86,91,1,62,55,92,234,880,7,81,52,63,84,251,20,49,98};
    for(int i=0; i<17; i++){
        insertByHash(code[i], name[i]);
    }
    cout << searchByHash(234, "Nigeria") << " " << searchByHash(250, "never") << endl;
    echo(removeByHash(234, "Nigeria"), " => deleted");
    cout << searchByHash(234, "Nigeria");
}