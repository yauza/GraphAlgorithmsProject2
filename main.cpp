#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <vector>


using namespace std;


class Node{
    int ind;

    Node(int ind){
        this->ind = ind;
    }

    void connect_to(int v){
        this->out.insert(v);
    }

public:
    unordered_set<int> out;
};

// A & B
unordered_set<int> intersection_of_two_sets(unordered_set<int> A, unordered_set<int> B){
    unordered_set<int> res;
    for(auto i : A){
        if(B.count(i) > 0) res.insert(i);
    }
    return res;
}

// A - B
unordered_set<int> difference_of_two_sets(unordered_set<int> A, unordered_set<int> B){
    for (const auto& i : B) {
        A.erase(i);
    }

}


vector<int> LexBFS(vector<Node> G){
    unordered_set<int> vertices;
    for(int i = 1; i < G.size()+1; i++){
        vertices.insert(i);
    }
    vector<unordered_set<int>> L;
    L.push_back(vertices);

    vector<int> lex;

    while(!L.empty()){
        int v = L[-1].back();
        L.pop_back();
        lex.push_back(v);

        vector<unordered_set<int>> temp_L;
        for(auto s : L){
            unordered_set<int> Y = intersection_of_two_sets(s, G[v].out);
            unordered_set<int> K = difference_of_two_sets(s, G[v].out);

            if(!Y.empty()) temp_L.push_back(Y);
            if(!K.empty()) temp_L.push_back(K);
        }
        L = temp_L;

    }

    return lex;

}


int main() {
    int T;
    scanf("%d", &T);

    while(T--){
        int N, M;
        scanf("%d %d", &N, &M);

        for(int i = 0; i < M; i++){
            int a, b;
            scanf("%d %d", &a, &b);
        }
    }


    return 0;
}
