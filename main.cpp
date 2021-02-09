#include <iostream>
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <vector>


using namespace std;


class Node{
public:
    int ind;
    unordered_set<int> out;

    void connect_to(int v){
        this->out.insert(v);
    }

    Node(int ind){
        this->ind = ind;
    }
};


void print_vector(vector<int> v){
    for(auto i : v) cout << i << " ";
    cout << endl;
}

void print_vector_of_sets(vector<unordered_set<int>> v){
    int k = 0;
    for(auto i : v){
        cout << k << ": ";
        for(auto j : i){
            cout << j << " ";
        }
        cout << endl;
        k++;
    }
}

void print_unordered_set(unordered_set<int> s){
    for(auto i : s) cout << i << " ";
    cout << endl;
}


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
    return A;
}


vector<int> LexBFS(vector<Node*> G){
    unordered_set<int> vertices;
    for(int i = 1; i < G.size(); i++){
        vertices.insert(i);
    }
    //cout << "vertices done" << endl;
    vector<unordered_set<int>> L;
    L.push_back(vertices);

    vector<int> lex;

    while(!L.empty()){
        //cout << "start petli" << endl;
        //print_vector_of_sets(L);
        int v = *L[L.size()-1].begin();
        L[L.size()-1].erase(L[L.size()-1].begin());

        //cout << "v: " << v << endl;
        //L.pop_back();
        lex.push_back(v);
        //cout << "koniec pop_back" << endl;
        //print_vector_of_sets(L);

        vector<unordered_set<int>> temp_L;
        for(auto s : L){
            //cout << "\n***" << endl;
            //cout << "G[v]->out: ";
            //print_unordered_set(G[v]->out);

            unordered_set<int> Y = intersection_of_two_sets(s, G[v]->out);
            //cout << "Y: ";
            //print_unordered_set(Y);

            unordered_set<int> K = difference_of_two_sets(s, G[v]->out);
            //cout << "K: ";
            //print_unordered_set(K);

            if(!K.empty()) temp_L.push_back(K);
            if(!Y.empty()) temp_L.push_back(Y);

            //cout << "temp_L: ";
            //print_vector_of_sets(temp_L);

            //cout << "***" << endl;
        }
        L = temp_L;
        //cout << "koniec petli" << endl;
    }

    return lex;

}


bool is_cycle(vector<Node*> G, vector<bool>& visited, int v, int parent){
    visited[v] = true;

    for(auto i : G[v]->out){
        if(!visited[i]){
            if(is_cycle(G, visited, i, v)) return true;
        }else if(i != parent) return true;
    }

    return false;
}


bool is_tree(vector<Node*> G){
    vector<bool> visited(G.size()+1, false);
    visited[0] = true;

    if(is_cycle(G, visited, 1, 0)) return false;

    for(int i = 0; i < G.size(); i++){
        if(!visited[i]) return false;
    }

    return true;
}


int solve(vector<Node*> G){

    if(is_tree(G)) return 2;

    vector<int> peo = LexBFS(G);
    int max_clique_size = 0;

    for(int i = 1; i < peo.size(); i++){
        int temp_clique_size = 0;
        for(int j = 0; j < i; j++){
            if(G[peo[i]]->out.count(peo[j])) temp_clique_size++;
        }
        max_clique_size = max(max_clique_size, temp_clique_size);
    }

    return max_clique_size;
}


int main() {
    int T;
    scanf("%d", &T);

    while(T--){
        int N, M;
        scanf("%d %d", &N, &M);

        vector<Node*> G(N+1);
        for(int i = 1; i < N+1; i++){
            Node* new_node = new Node(i);
            G[i] = new_node;
        }

        for(int i = 0; i < M; i++){
            int a, b;
            scanf("%d %d", &a, &b);
            G[a]->connect_to(b);
            G[b]->connect_to(a);
        }

        int res = solve(G);
        printf("%d\n", res);
    }


    return 0;
}
