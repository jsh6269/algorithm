#include <iostream>
#include <list>
#include <map>
#include <string>
#include <cmath>
using namespace std;

string LZWDecompress(list<int> compressed, int numBits){
    // time complexity: O(n)
    // 32: 공백, 65~90: A~Z, 97~122: a~z, 128~: custom
    int maxCode = (int)pow(2, numBits) - 1;
    string decompressed;
    map<int, string> decTable;

    int code = 128;
    for(int i=0; i<code; i++){
        string temp;
        decTable.insert({i, temp.append(1, char(i))});
    }
    int encNum = compressed.front();
    compressed.pop_front();
    string dec = decTable.find(encNum)->second;
    decompressed += dec;
    string prev_dec = dec;

    for(int enc : compressed){
        if(decTable.count(enc) == 0){
            dec = prev_dec + prev_dec[0];
        }
        else{
            dec = decTable.find(enc)->second;
        }
        decompressed += dec;
        if(code <= maxCode){
            decTable.insert({code, prev_dec + dec[0]});
            code++;
        }
        prev_dec = dec;
    }
    return decompressed;
}

int main(){
    list<int> exampleLst1 {77, 69, 76, 76, 79, 87, 32, 89, 129, 131, 133, 70, 136, 132};
    list<int> exampleLst2 {65, 66, 128, 130};
    string ans1 = LZWDecompress(exampleLst1, 8);
    cout << ans1 << "\n";
    string ans2 = LZWDecompress(exampleLst2, 8);
    cout << ans2;

}