#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

long long linearCongruential(long long x){
    long long m = (long long)pow(2, 32);
    long long a = 1664525;
    long long c = 1013904223;
    a %= m;
    x %= m;
    c %= m;
    return (a * x + c) % m;
}

int main(){
    ofstream fout;
    fout.open("./01_random16384.txt");
    long long s = 12523;
    for(int i=0; i<16384; i++){
        s = linearCongruential(s);
        cout << s << endl;
        fout << s << endl;
    }
    fout.close();
}


