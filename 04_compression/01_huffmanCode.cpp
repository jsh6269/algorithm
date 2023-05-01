#include <iostream>
#include <functional>
#include <queue>
using namespace std;

struct Node {
    char letter;
    int cnt;
    struct Node *leftNode;
    struct Node *rightNode;

    bool operator<(const Node n) const {
        return this->cnt > n.cnt;
    }
};

struct Node CreateHuffmanCode(priority_queue<struct Node>pq, struct Node* alloc){
    // time complexity: O(nlogn)
    int pos = 0;
    while(pq.size() > 1){
        alloc[pos++] = pq.top();
        pq.pop();
        alloc[pos++] = pq.top();
        pq.pop();
        int sum = alloc[pos-2].cnt + alloc[pos-1].cnt;
        struct Node newNode = {'\0', sum, &alloc[pos-2],  &alloc[pos-1]};
        pq.push(newNode);
    }
    return pq.top();
}

void descTree(struct Node *ans, string code){
    if(ans->letter != '\0'){
        cout << ans->letter << ": " << code << "\n";
        return;
    }
    descTree(ans->leftNode, code+"0");
    descTree(ans->rightNode, code+"1");
}

int main(){
    priority_queue<struct Node> pq;
    char letter[7] = {'R', 'N', 'V', 'S', 'C', 'F', 'E'};
    int cnt[7] = {1, 1, 1, 1, 2, 2, 5};
    for(int i=0; i<7; i++){
        struct Node n = {letter[i], cnt[i], nullptr, nullptr};
        pq.push(n);
    }
    auto* alloc = (struct Node*)malloc(sizeof(struct Node*) * 100);
    struct Node ans = CreateHuffmanCode(pq, alloc);
    descTree(&ans, "");
    free(alloc);
    return 0;
}