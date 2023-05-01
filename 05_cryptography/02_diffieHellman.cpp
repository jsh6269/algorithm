#include <iostream>
#include <utility>
using namespace std;
long long modExpRepeatedSquaring(long long, long long, long long);

const int p = 23;
const int g = 14;

class Person{
private:
    int a{}, ex{}, B{}, key{};
    string name;
public:
    explicit Person(string name){
        this->name = std::move(name);
    }
    int exchange_value(){
        this->ex = (int)modExpRepeatedSquaring(g, this->a, p);
        return this->ex;
    }
    void setA(int a_value){
        this->a = a_value;
    }
    void getB(int b_value){
        this->B = b_value;
    }
    void make_key(){
        this->key = (int) modExpRepeatedSquaring(B, this->a, p);
    }
    void show_key(){
        cout << this->name << "'s key: " << this->key << endl;
    }
};

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
    Person alice = Person("Alice");
    Person bob = Person("Bob");

    alice.setA(3);
    bob.setA(4);

    alice.getB(bob.exchange_value());
    bob.getB(alice.exchange_value());

    alice.make_key();
    bob.make_key();

    alice.show_key();
    bob.show_key();
    return 0;
}