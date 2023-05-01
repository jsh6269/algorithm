#include <iostream>
#include <cmath>
#include <random>
using namespace std;

int encrypt_otp(int plain_text, int pad){
    return plain_text ^ pad;
}

int decrypt_otp(int cipher_text, int pad){
    return cipher_text ^ pad;
}

int main(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> rand(0, 1000000);

    int plain_text = 52345;
    // pad has to be secured
    int pad = (int)floor(rand(gen));
    int cipher_text = encrypt_otp(plain_text, pad);
    cout << decrypt_otp(cipher_text, pad);
    return 0;
}