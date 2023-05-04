#include <iostream>
#include <utility>
#include <random>
using namespace std;

pair<int, int> factorTwo(int n){
    // n = 2^r * q
    int q = n;
    int r = 0;
    while(q % 2 == 0){
        r++;
        q/=2;
    }
    return make_pair(r, q);
}

long long modExpRepeatedSquaring(long long g, long long x, long long p){
    // g^x mod p
    // time complexity: O((logp)^3)
    long long c = g % p;
    long long d = x;
    long long r = 1;
    while(d > 0){
        if(d % 2 == 1)
            r = (r * c) % p;
        d = d / 2;
        c = (c * c) % p;
    }
    return r;
}

bool witnessComposite(int p){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> rand(2, p);

    pair<int, int> pp = factorTwo(p-1);
    int r = pp.first, q = pp.second;
    int x = floor(rand(gen));
    long long y = modExpRepeatedSquaring(x, q, p);
    if(y == 1)
        return false;
    for(int j=0; j<r; j++){
        if(y == p-1)
            return false;
        y = (y * y) % p;
        if(y == 1)
            return true;
    }
    return true;
}

bool millerRabinPrimalityTest(int p, int rep){
    // time complexity: O(rep * (logp)^3)
    if(p == 2)
        return true;
    if(p % 2 == 0)
        return false;

    for(int i=0; i<rep; i++){
        if(witnessComposite(p))
            return false;
    }
    return true;
}

int main(){
    // prime number
    cout << millerRabinPrimalityTest(27644437, 10000) << endl;
    // composite number
    cout << millerRabinPrimalityTest(272543, 10000) << endl;
    // prime number
    cout << millerRabinPrimalityTest(2147483647, 10000) << endl;
    return 0;
}