#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

struct vertex {
    int value;
    vector<int> edges;
    vertex (int v) {
	value = v;
    }
};
    
class graph {
public:
    map<int, vertex*> vertices;

    void add_edge(int u, int v, int w) {
	vertex *uu = find(u);
	vertex *vv = find(v);

	if (uu == nullptr) {
	    uu = new vertex(u);
	    vertices.insert({u, uu});
	}
	if (vv == nullptr) {
	    vv = new vertex(v);
	    vertices.insert({v, vv});
	}

	uu->edges.push_back(v);
    }

    void dfs() {
	bool c = false;
	for (auto it : vertices) {
	    vertex *v = it.second;
	    unordered_set<int> vis;
	    dfs_visit(v, vis, &c);

	    if (c == true) {
		cout << "true ";
		return;
	    }
	}

	cout << "false ";
    }

    void dfs_visit(vertex *v,unordered_set<int>  visited, bool *c) {
	visited.insert(v->value);

	for (int i = 0; i < v->edges.size(); i++) {
	    if (visited.find(v->edges[i]) != visited.end()) {
	       *c = true;
	       return;
	   }
	   else {
	       vertex *u = find(v->edges[i]);
	       dfs_visit(u, visited, c);
	   }
	}
	visited.erase(v->value);
    }
    
    vertex* find(int key) {
	vertex *v = nullptr;
	auto it = vertices.find(key);
	if (it != vertices.end()) {
	    v = it->second;
	}
	return v;
    }
};


int main() {
    int t;
    cin >>t;
    for (int j = 0; j < t; j++) {
        graph g;
        int v, e;
        cin >> v >> e;
        int x, y, z;
        for (int i = 0; i < e; i++) {
            cin >> x >> y >> z;
            g.add_edge(x, y, z);
        }
        g.dfs();
    }
    return 0;
}
