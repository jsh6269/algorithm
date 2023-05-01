#include <iostream>
#include <tuple>
#include <cmath>
#include <utility>
using namespace std;
tuple<int, int, int> extendedEuclid(int, int);
int modularInverse(int, int);
long long modExpRepeatedSquaring(long long, long long, long long);
unsigned int hashed(const string&);

class Alice{
private:
    int p, q, n, e, d;
    int X;
    pair<int, int> privateKey;
    string plain;
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
    void setPlain(string plain_text){
        this->plain = plain_text;
    }
    pair<string, int> getSignedText(){
        int hash = (int)hashed(plain);
        int cipher = (int)modExpRepeatedSquaring(hash, privateKey.first, privateKey.second);
        return make_pair(plain, cipher);
    }
};

class Bob{
public:
    pair<int, int> publicKey;
    void setPublicKey(pair<int, int> publicKey){
        this->publicKey = publicKey;
    }
    bool verifySignature(pair<string, int> signedText){
        int hash1 = (int)hashed(signedText.first);
        int hash2 = (int)modExpRepeatedSquaring(signedText.second, publicKey.first, publicKey.second);
        cout << "hash1: " << hash1 << endl << "hash2: " << hash2 << endl;
        return hash1 == hash2;
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

unsigned int hashed(const string& str){
    unsigned int hash = 0x811C9DC5;
    long long unsigned int p  = 0x01000193;
    hash = hash ^ 352;
    for(char c : str){
        hash = hash ^ (unsigned int)c;
        hash = (unsigned int)((hash * p) & 0xFFFFFFF);
    }
    return hash;
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
    string plain = "Hello, world!";
    Alice alice = Alice();
    Bob bob = Bob();

    alice.setPQ(104701, 13709);
    alice.setE(331);
    alice.setD();

    alice.setPlain(plain);
    pair<string, int> signedText = alice.getSignedText();

    bob.setPublicKey(alice.getPublicKey());
    bool isAlice = bob.verifySignature(signedText);
    cout << isAlice;

    return 0;
}