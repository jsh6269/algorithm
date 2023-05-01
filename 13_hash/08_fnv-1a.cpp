#include <iostream>
using namespace std;

unsigned int FNV_1a(const string& str, unsigned int i){
    // hash function for bloom filter
    unsigned int hash = 0x811C9DC5;
    long long unsigned int p  = 0x01000193;
    hash = hash ^ i;
    for(char c : str){
        hash = hash ^ (unsigned int)c;
        hash = (unsigned int)((hash * p) & 0xFFFFFFFF);
    }
    return hash;
}

int main(){
    for(unsigned int i=0; i<5; i++){
        cout << FNV_1a("hello", i) << " ";
    }
    return 0;
}