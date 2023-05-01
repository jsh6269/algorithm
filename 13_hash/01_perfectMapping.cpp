#include <iostream>
using namespace std;

int code(char c){
    int ascii = (int)c;
    int ans = 0;
    if(65 <= ascii && ascii <= 90){
        ans = ascii - 64;
    }
    if(97 <= ascii && ascii <=122){
        ans = ascii - 96;
    }
    return (ans > 18) ? (ans + 3) : (ans > 9 ? ans + 1 : ans);
}

int perfectMapping(string str){
    int len = (int)str.length();
    int ref = -code(str[0]);
    int s = (len > 1) ? code(str[1]) : 0;
    ref = ref - 8 + s;
    if(ref <= 0){
        ref = ref + 16 + s;
    }
    s = (len > 2) ? code(str[2]) : 0;
    if(s == 0){
        return ref;
    }
    ref = ref - 28 + s;
    if(ref > 0){
        return ref;
    }
    ref = ref + 11 + s;
    int t = code(str[3]);
    if(t == 0){
        return ref;
    }
    ref = ref - s + 5;
    if(ref < 0){
        return ref;
    }
    ref += 10;
    return ref;
}

int main(){
    string words[31] = {"a","and","are","as","at","be","but","by","for",
                        "from","had","have","he","her","his", "i","in",
                        "is","it","not","of","on","or","that","the",
                        "this","to","was","which","with","you"};
    for(int i=0; i< 31; i++){
        if(i != 0 && i % 12 == 0)
            cout << endl;
        cout << words[i] << ": " << perfectMapping(words[i]) << ", ";
    }
    return 0;
}