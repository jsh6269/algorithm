#include <iostream>
#include <queue>
#include <map>
#include <sstream>
#include <string>
using namespace std;
// f(state), state representation, # of moves to get there
using tisi = tuple<int, string, int>;

int** create2DArray(int height, int width=-1, int value=-1){
    int **arr;
    width = (width == -1) ? height : width;
    arr = (int**) malloc ( sizeof(int*) * height);
    for(int i=0; i<height; i++){
        arr[i] = (int*) malloc ( sizeof(int) * width);
        for(int j=0; j<width; j++){
            arr[i][j] = value;
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

int g(string state, string dest, int n){
    // sum of taxi distance difference for every cubic between two puzzle
    map<int, pair<int, int>> stateCash;
    istringstream ss(state);
    istringstream sd(dest);
    string frac;
    int cnt = 0;
    while(getline(ss, frac, ' ')){
        stateCash.insert({stoi(frac), make_pair(cnt/n, cnt&n)});
        cnt++;
    }
    cnt = 0;
    int g_val = 0;
    while(getline(sd, frac, ' ')){
        int val = stoi(frac);
        if(val != 0){
            g_val += abs(cnt/n - stateCash[val].first) + abs(cnt%n - stateCash[val].second);
        }
    }
    return g_val;
}

string makeMove(string state, string move, int n){
    int** puzzle = create2DArray(n);
    istringstream ss(state);
    string frac;
    int cnt = 0;
    int markR, markC;
    while(getline(ss, frac, ' ')){
        puzzle[cnt/n][cnt%n] = stoi(frac);
        if(stoi(frac) == 0){
            markR = cnt / n;
            markC = cnt % n;
        }
        cnt++;
    }
    int nextR = markR, nextC = markC;
    if(move == "up"){
        nextR--;
    }
    if(move == "down"){
        nextR++;
    }
    if(move == "left"){
        nextC--;
    }
    if(move == "right"){
        nextC++;
    }
    if(nextR < 0 || nextR == n || nextC < 0 || nextC == n){
        freeArray(puzzle, n);
        return "N/A";
    }
    swap(puzzle[markR][markC], puzzle[nextR][nextC]);

    string nextState;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            nextState.append(to_string(puzzle[i][j]));
            if(i != n-1 || j != n-1){
                nextState.append(" ");
            }
        }
    }
    freeArray(puzzle, n);
    return nextState;
}


pair<int, string> n_puzzle(string start, string dest, int n){
    // a* algorithm is used which is a heuristic approach
    priority_queue<tisi, vector<tisi>, greater<>> pq;
    map<string, int> dist;
    map<string, string> path;
    string moves[4] = {"left", "right", "up", "down"};
    bool success = false;

    pq.emplace(g(start, dest, n) + 0, start, 0);
    dist[start] = 0;
    path[start] = "";

    while(!pq.empty()){
        tisi item = pq.top(); pq.pop();
        string state = get<1>(item);
        if(state == dest){
            success = true;
            break;
        }
        for(auto & move : moves){
            string nextState = makeMove(state, move, n);
            if(nextState != "N/A"){
                if(dist.find(nextState) == dist.end() || dist[nextState] > get<2>(item) + 1){
                    dist[nextState] = get<2>(item) + 1;
                    path[nextState] = path[state] + move + " ";
                    pq.emplace(g(nextState, dest, n) + get<2>(item) + 1, nextState, dist[nextState]);
                }
            }
        }
    }
    return make_pair(success ? dist[dest] : -1, path[dest]);
}

int main(){
//    auto ans = n_puzzle("0 1 2 3 4 5 6 7 8", "1 2 5 3 4 8 6 0 7", 3);
    auto ans = n_puzzle("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15", "4 1 2 3 5 6 10 7 8 9 14 11 12 13 15 0", 4);
    cout << ans.first << endl << ans.second;

    return 0;
}