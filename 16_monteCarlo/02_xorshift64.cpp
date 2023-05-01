#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

unsigned long long xorShift64Star(unsigned long long x){
    x = x ^ (x >> 12);
    x = x ^ (x << 25);
    x = x ^ (x >> 27);
    return x * 26858216577363817ULL;
}

int main(){
    ofstream fout;
    fout.open("./02_random16384.txt");
    unsigned long long s = 12523;
    for(int i=0; i<16384; i++){
        s = xorShift64Star(s);
        cout << s << endl;
        fout << s << endl;
    }
    fout.close();
}


