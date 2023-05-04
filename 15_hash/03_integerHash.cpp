#include <iostream>
using namespace std;

struct nation{
    int key{};
    string name;
};

int integerHash(int k, int m){
    return k % m;
}

int main(){
    nation top17[23];
    string name[17] = {"China","India","USA","Indonesia","Brazil", "Pakistan","Nigeria",
                       "Bangladesh","Russia","Japan","Mexico","Philippines","Vietnam",
                       "Ethiopia","Egypt","Germany","Iran"};
    int code[17] = {86,91,1,62,55,92,234,880,7,81,52,63,84,251,20,49,98};
    for(int i=0; i<17; i++){
        int hash = integerHash(code[i], 23);
        top17[hash] = {code[i], name[i]};
        cout << "hash: " << hash << "    name: " << name[i] << endl;
    }
    return 0;
}