#include <iostream>
#include <tuple>
#include <cmath>
using namespace std;

int euclid(int a, int b){
    return b == 0 ? a : euclid(b, a % b);
}

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

int main(){
    cout << euclid(17, 352) << endl;
    tuple<int, int, int> ans = extendedEuclid(17, 352);
    int r = get<0>(ans);
    int x = get<1>(ans);
    int y = get<2>(ans);
    cout << r << " = " << 17 << " * " << x << " + " << 352 << " * " << y;

}