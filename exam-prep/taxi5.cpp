#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

struct edge;

struct vertex {
    int key;
    map<int, edge*> edges;
    vertex(int k) {
	key = k;
    }
};

struct edge {
    vertex *u;
    vertex *v;
    int w;
    bool r;
    edge (vertex *from, vertex *to, int wght, bool rev = false) {
	u = from;
	v = to;
	w = wght;
	r = rev;
    }
};

struct graph {
    vector<vertex*> vertices;
    vector<int> sett;
    vector<int> parent; 
    
    int max;
    graph(int vs) {
	for (int i = 0; i <= vs; i++) {
	    vertices.push_back(new vertex(i));
	    sett.push_back(i);
	    parent.push_back(-1);
	}
	max = 0;
    }

    void add_edge(int u, int v, int w) {
	vertex *uu = vertices[u];
	vertex *vv = vertices[v];
	uu->edges.insert({v, new edge(uu, vv, w)});
	
	int uset = find_set(u);
	int vset = find_set(v);
	if (uset == vset) {
	    edge *e = new edge(uu, vv, w);
	    cout << u << " " << v << " " << w << endl;
	    find_lightest_edge(e);
	    
	}
	else {
	    union_sets(uset, vset);
	}
    }

    void find_lightest_edge (edge *e) {
	vector<bool> visited(vertices.size(), false);
	edge *path = new edge(nullptr, nullptr, 1046576);
	edge *min = new edge(nullptr, nullptr, 1046576);

	dfs(e->u, visited, path, min);
	cout << endl;
	if (min->w != 1046576 && max < min->w) {
	    max = min->w;
	}
	if (min->w != 1046576) {
	    cout << min->u->key << " " << min->v->key << " " << min->w << endl;
	    vertex *u = min->u;
	    u->edges.erase(min->v->key);
	    vertex *v = min->v;
	    v->edges.insert({u->key, new edge(v, u, min->w, true)});
	    delete min;
	}
    }

    void dfs(vertex *v,vector<bool> visited, edge* path, edge* min) {
	visited[v->key] = true;
	cout << v->key << " ";
	for (auto it: v->edges) {
	    cout << it.second->v->key << " ";
	    if (visited[it.second->v->key]) {
	        if (min->w > path->w) {
		    min->w = path->w;
		    min->u = path->u;
		    min->v = path->v;
		}
	    }
	    else {
		if (path->w > it.second->w) {
		    path->w = it.second->w;
		    path->u = it.second->u;
		    path->v = it.second->v;
		}
		dfs(it.second->v, visited, path,min); 
	    }
	}
    }

    void print_max() {
	cout << max << endl;
    }
    
    int find_set(int i) {
	if (i == sett[i]) {
	    return i;
	}
	sett[i] = find_set(sett[i]);
	return sett[i];
    }

    void union_sets(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (a != b) {
	    sett[b] = a;
	}
    }
};

int main() {

    int vertices, edges;
    cin >> vertices >> edges;

    graph g(vertices);
    int u, v, w;
    for (int i = 0; i < edges; i++) {
	cin >> u >> v >> w;
	g.add_edge(u, v, w);
    }
    g.print_max();
}
