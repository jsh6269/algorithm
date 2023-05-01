#include <iostream>
#include <tuple>
#include <cmath>
using namespace std;
tuple<int, int, int> extendedEuclid(int, int);
int modularInverse(int, int);
long long modExpRepeatedSquaring(long long, long long, long long);

class Alice{
private:
    int p, q, n, e, d;
    int X;
    pair<int, int> privateKey;
    int plain;
public:
    pair<int, int> publicKey;
    void setPQ(int p_val, int q_val){
        this->p = p_val;
        this->q = q_val;
        this->n = p * q;
        this->X = (p-1) * (q-1);
    }
    bool setE(int e_val){
        if(get<0>(extendedEuclid(e_val, X)) != 1){
            return false;
        }
        this->e = e_val;
        publicKey = make_pair(this->e, n);
        return true;
    }
    void setD(){
        this->d = modularInverse(e, X);
        privateKey = make_pair(d, n);
    }
    pair<int, int> getPublicKey(){
        return publicKey;
    }
    void decrypt(int cipher){
        plain = (int)modExpRepeatedSquaring(cipher, privateKey.first, privateKey.second);
    }
    void showText(){
        cout << plain << endl;
    }
};

class Bob{
private:
    int plain;
public:
    pair<int, int> publicKey;
    void setPlain(int plain_text){
        this->plain = plain_text;
    }
    void setPublicKey(pair<int, int> publicKey){
        this->publicKey = publicKey;
    }
    int getCipher(){
        return (int)modExpRepeatedSquaring(plain, publicKey.first, publicKey.second);
    }
};

tuple<int, int, int> extendedEuclid(int a, int b){
    if(b == 0){
        return make_tuple(a, 1, 0);
    }
    tuple<int, int, int> ret = extendedEuclid(b, a % b);
    int r = get<0>(ret);
    int x = get<1>(ret);
    int y = get<2>(ret);

    return make_tuple(r, y, x - (int)floor((double)a / b) * y);
}

int modularInverse(int a , int n){
    tuple<int, int, int> ret = extendedEuclid(a, n);
    int r = get<0>(ret);
    int x = get<1>(ret);

    if(r != 1){
        return 0;
    }
    if(x < 0){
        return x + n;
    }
    return x;
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


int main(){
    int plain = 314;
    Alice alice = Alice();
    Bob bob = Bob();

    alice.setPQ(17, 23);
    alice.setE(3);
    alice.setD();

    bob.setPlain(plain);
    bob.setPublicKey(alice.getPublicKey());

    int cipher = bob.getCipher();
    alice.decrypt(cipher);
    alice.showText();

    return 0;
}