#include <iostream>
#include <utility>
#include <string>
using namespace std;

int** create2DArray(int height, int width=-1, int init=-1){
    int **arr;
    width = (width == -1) ? height : width;
    arr = (int**) malloc ( sizeof(int*) * height);
    for(int i=0; i<height; i++){
        arr[i] = (int*) malloc ( sizeof(int) * width);
        for(int j=0; j<width; j++){
            arr[i][j] = init;
        }
    }
    return arr;
}

void freeArray(int **arr, int height){
    for(int i=0; i<height; i++){
        free(arr[i]);
    }
    free(arr);
}

pair<int, string> longestCommonSubstring(string s1, string s2){
    // time complexity: O(|s1||s2|)
    int** dy = create2DArray((int)s1.length(), (int)s2.length(), 0);
    // dy[i][j] = s1[i], s2[j]를 말단으로 포함하는 longest common substring의 길이
    for(int i=0; i<s1.length(); i++){
        for(int j=0; j<s2.length(); j++){
            if(s1[i] == s2[j]){
                dy[i][j] = (i==0 || j==0) ? 1 : dy[i-1][j-1] + 1;
            }
            else{
                dy[i][j] = 0;
            }
        }
    }
    int max = 0;
    int loc = -1;
    for(int i=0; i<s1.length(); i++){
        for(int j=0; j<s2.length(); j++){
            if(dy[i][j] > max){
                max = dy[i][j];
                loc = i;
            }
        }
    }
    string substring;
    for(int i=0; i<max; i++){
        substring.insert(0, 1, s1[loc-i]);
    }
    freeArray(dy, (int)s1.length());
    return make_pair(max, substring);
}

pair<int, string> longestCommonSubsequence(string s1, string s2) {
    // time complexity: O(|s1||s2|)
    // dy[i][j] = s1[i], s2[j]지점까지의 문자열에 대한 longest common subsequence의 길이
    int** dy = create2DArray((int)s1.length(), (int)s2.length(), 0);
    for(int i=0; i<s1.length(); i++){
        for(int j=0; j<s2.length(); j++){
            if(s1[i] == s2[j]){
                dy[i][j] = (i==0 || j==0) ? 1 : dy[i-1][j-1] + 1;
            }
            else{
                dy[i][j] = max(i==0 ? 0 : dy[i-1][j], j==0 ? 0 : dy[i][j-1]);
            }
        }
    }

    int i = (int)s1.length()-1, j = (int)s2.length()-1;
    string subsequence;
    int length = 0;
    while(i!=-1 && j!=-1 && dy[i][j] != 0){
        if(i!=0 && dy[i-1][j] == dy[i][j]){
            i--;
        }
        else if(j!=0 && dy[i][j-1] == dy[i][j]){
            j--;
        }
        else{
            length++;
            subsequence.insert(0, 1, s1[i]);
            i--, j--;
        }
    }
    return make_pair(length, subsequence);
}

int main(){
    string s1 = "ABCDEF";
    string s2 = "GKBCDFEGB";
    pair<int, string> ans = longestCommonSubstring(s1, s2);
    cout << ans.first << ": ";
    cout << ans.second << endl;
    ans = longestCommonSubsequence(s1, s2);
    cout << ans.first << ": ";
    cout << ans.second << endl;
    return 0;
}