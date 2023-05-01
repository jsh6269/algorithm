#include <iostream>
#include <algorithm>
using namespace std;

int ordinal(char c){
    int ascii = (int)c;
    int ans = 0;
    if(65 <= ascii && ascii <= 90){
        ans = ascii - 65;
    }
    if(97 <= ascii && ascii <=122){
        ans = ascii - 97;
    }
    return ans;
}

int minimalPerfectMapping(string str){
    int C[26] = {3,23,-1,17,7,11,-1,5,0,-1,-1,-1,16,17,
                 9,-1,-1,13,4,0,23,-1,8,-1,4,-1};
    int len = str.length();
    int a = ordinal(str[0]);
    int b = ordinal(str[len-1]);
    return len + C[a] + C[b];
}
int main(){
    string words[31] = {"a","and","are","as","at","be","but","by","for",
                        "from","had","have","he","her","his", "i","in",
                        "is","it","not","of","on","or","that","the",
                        "this","to","was","which","with","you"};
    int gets[31];
    for(int i=0; i< 31; i++){
        if(i != 0 && i % 12 == 0)
            cout << endl;
        gets[i] = minimalPerfectMapping(words[i]);
        cout << words[i] << ": " << gets[i] << ", ";
    }
//    cout << endl;
//    sort(gets, gets+31);
//    for(int get : gets){
//        cout << get << " ";
//    }
    return 0;
}