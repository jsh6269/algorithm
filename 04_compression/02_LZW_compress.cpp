#include <iostream>
#include <list>
#include <map>
#include <string>
#include <cmath>
using namespace std;

list<int> LZWCompress(string text, int numBits){
    // time complexity: O(n)
    // 32: 공백, 65~90: A~Z, 97~122: a~z, 128~: custom
    list<int> compressed;
    int maxCode = (int)pow(2, numBits) - 1;
    int code = 128;

    map<string, int> table;
    for(int i=0; i<code; i++){
        string tmp;
        table.insert({tmp.append(1, char(i)), i});
    }

    string w;
    for(char const &c : text){
        string wc = w + c;
        if(table.count(wc) != 0){
            w = wc;
        }
        else{
            int encNum = table.find(w)->second;
            compressed.push_back(encNum);
            w = c;
            if(code <= maxCode){
                table.insert({wc, code});
                code++;
            }
        }
    }
    if(!w.empty()){
        compressed.push_back(table.find(w)->second);
    }
    return compressed;
}

int main(){
    list<int> ans = LZWCompress("MELLOW YELLOW FELLOW", 8);
    for(int val : ans){
        cout << val << " ";
    }
}