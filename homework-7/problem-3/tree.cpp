#include <iostream>
#include <vector>
#include <set>

using namespace std;
int mx;

struct node {
    int coffee;
    int key;
    vector<node*> edges;

    node (int coffee) {
        this->coffee = coffee;
    }

    bool is_leaf() {
        return this->edges.size() == 1 &&
	       this->key != 1;
    }
};

void create_nodes(node **nodes, int n) {
    int c;
    for (int i = 1; i < n; i++) {
        cin >> c;
        nodes[i] = new node(c);
    }
}

void count_paths(node *root, int &paths, int s, set<int> visited) {
    if (root->is_leaf()) {
        if (root->coffee == 0) {
             paths += 1;
        }
        else if(root->coffee == 1 && s >= 1) {
            paths += 1;
        }
        
        return;
    }
    
    visited.insert(root->key);
    for (int i = 0; i < root->edges.size(); i++) {
        if (visited.find(root->edges[i]->key) == visited.end()) {
            if (root->coffee == 0) {
                count_paths(root->edges[i], paths, mx, visited);
            }
            if (root->coffee == 1 && s >= 1) {
                count_paths(root->edges[i], paths, s - 1, visited);
            }
        }
    }
}


int main() {
    int n;
    cin >> n >> mx;
    n += 1;

    node **nodes = new node*[n];
    create_nodes(nodes, n);

    int k, j;
    for (int i = 1; i < n - 1; i++) {
        cin >> k >> j;
        nodes[k]->key = k;
        nodes[j]->key = j;
        nodes[k]->edges.push_back(nodes[j]);
        nodes[j]->edges.push_back(nodes[k]);
    }

    int paths = 0;
    int current = mx;
    set<int> visited;
    count_paths(nodes[1], paths, current, visited);
    cout << paths << endl;
}
