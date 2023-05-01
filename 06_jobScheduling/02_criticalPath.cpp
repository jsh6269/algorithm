#include <iostream>
#include <tuple>
#include <list>
#include <stack>
#include <unordered_set>

using namespace std;
void topologicalSort(int[][12], int);
void DFSTopologicalSort(int[][12], int, int);
int find_terminal(const int*, const unordered_set<int>&);

list<int> sorted;
bool visited[100];

tuple<int*, int*, int> criticalPath(int graph[][12], int n, unordered_set<int> giver, const unordered_set<int>& receiver){
    // optimal time complexity: O(|V|+|E|)
    // to make this algorithm optimal, need to use both matrix form and List form to describe the graph
    int* pred = (int*) malloc(sizeof(int) * n);
    int* dist = (int*) malloc(sizeof(int) * n);

    fill_n(pred, n, -1);
    fill_n(dist, n, -1);
    for(int i=0; i<n; i++){
        if(giver.find(i) != giver.end()){
            dist[i] = 0;
        }
    }

    topologicalSort(graph, n);
    for(int u : sorted){
        for(int i=0; i<n; i++){
            if(graph[u][i] != -1 && dist[i] < dist[u] + graph[u][i]){
                dist[i] = dist[u] + graph[u][i];
                pred[i] = u;
            }
        }
    }
    int terminal = find_terminal(dist, receiver);
    return make_tuple(pred, dist, terminal);
}

int find_terminal(const int* dist, const unordered_set<int>& receiver){
    // finding terminal of critical path
    int max = -1, maxID;
    for(int v : receiver){
        if(dist[v] > max){
            max = dist[v];
            maxID = v;
        }
    }
    return maxID;
}

void topologicalSort(int graph[][12], int n){
    // time complexity: O(|V|+|E|)
    for(int i=0; i<n; i++){
        if(!visited[i]){
            DFSTopologicalSort(graph, n, i);
        }
    }
}

void DFSTopologicalSort(int graph[][12], int n, int node){
    visited[node] = true;
    for(int i=0; i<n; i++){
        if(graph[node][i] != -1 && !visited[i]){
            DFSTopologicalSort(graph, n, i);
        }
    }
    sorted.push_front(node);
}

void back_track(tuple<int*, int*, int> ans){
    int* pred = get<0>(ans);
    int* dist = get<1>(ans);
    int terminal = get<2>(ans);
    int loc = terminal;
    stack<int> S;

    cout << "total cost: " << dist[terminal] << endl;
    while(loc != -1){
        S.push(loc);
        loc = pred[loc];
    }
    while(!S.empty()){
        cout << S.top() << " ";
        S.pop();
    }
}

int main(){
    int graph[12][12];
    fill_n(*graph, 12*12, -1);

    int edges[13][3]={{0,1,17},{5,6,11},{5,9,15},
                     {1,2,13},{6,7,18},{9,10,14},
                     {2,3,9},{7,3,16},{10,11,17},
                     {7,11,19},{3,8,10},{7,8,13},
                     {3,4,11}};

    unordered_set<int> giver = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    unordered_set<int> receiver = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for(auto & edge : edges){
        giver.erase(edge[1]);
        receiver.erase(edge[0]);
        graph[edge[0]][edge[1]] = edge[2];
    }
    tuple<int*, int*, int> ans = criticalPath(graph, 12, giver, receiver);
    back_track(ans);
    return 0;
}