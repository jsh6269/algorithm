#include <iostream>
using namespace std;

int ordinal(char c){
    int ascii = (int)c;
    int ans = 0;
    if(65 <= ascii && ascii <= 90){
        ans = ascii - 65;
    }
    if(97 <= ascii && ascii <=122){
        ans = ascii - 97;
    }
    return ans;
}

int stringHash(string str, int b, int m){
    // time complexity: O(len(str))
    int h = 0;
    for(char c : str){
        h = (b * h + ordinal(c)) % m;
    }
    return h;
}

int main(){
    cout << "Hash value for 'hello': " << stringHash("Hello", 26, 31);
}