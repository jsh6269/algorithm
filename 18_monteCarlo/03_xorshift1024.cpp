#include <iostream>
#include <fstream>
using namespace std;
int p = 0;
unsigned long long xorShift1024Star(unsigned long long* S){
    unsigned long long s0 = S[p];
    p = (p + 1) & 15;
    unsigned long long s1 = S[p];
    s1 = s1 ^ (s1 << 31);
    s1 = s1 ^ (s1 >> 11);
    s0 = s0 ^ (s0 >> 30);
    S[p] = s0 ^ s1;
    return S[p] * 1181783497276652981ULL;
}

int main(){
    unsigned long long S[16] =
            {11120788862505236010ULL,11959114997911131045ULL,5943609330355904413ULL,1162489959827453111ULL,
            10527924870866291163ULL,8491984190110609175ULL,166895730617626955ULL,6378717760733673611ULL,
            16363733073951471570ULL,5712382298475009538ULL,8828962115227031798ULL,11722308445590076640ULL,
            11755773982338607650ULL,1977062879964875055ULL,2591093713777571575ULL,13412596966706764431ULL};
    ofstream fout;
    fout.open("./03_random16384.txt");

    for(int i=0; i<16384; i++){
        unsigned long long s = xorShift1024Star(S);
        fout << s << endl;
    }

    int cnt = 0;
    for(int i=0; i<1000000000; i++){
        unsigned long long ss1 = xorShift1024Star(S);
        unsigned long long ss2 = xorShift1024Star(S);
        long double a1 = ss1 / 18446744073709551615.0L;
        long double a2 = ss2 / 18446744073709551615.0L;
        if(a1 * a1 + a2 * a2 < 1)
            cnt++;
    }
    cout << cnt << " out of " << 1000000000 << endl;
    cout.precision(10);
    long double ratio = 4.0L * (long double)cnt / 1000000000.0L;
    cout << ratio;
    fout.close();
}


