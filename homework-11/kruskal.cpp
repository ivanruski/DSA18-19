#include <iostream>
#include <vector>
using namespace std;

struct edge {
    int u, v, w;
    edge (int u, int v, int w) {
	this->u = u;
	this->v = v;
	this->w = w;
    }
};

class graph {
public:
    int vertices;
    vector<edge> edges;  

    graph (int v) {
	vertices = v;
    }
    
    void add_edge(int u, int v, int w) {
	edges.push_back(edge(u,v,w));
    }

    void print_sorted() {
	this->sort_edges(0, edges.size() - 1);

	for (int i = 0; i < edges.size(); i++) {
	    cout << edges[i].u << " "
		 << edges[i].v
		 << " w: " << edges[i].w << endl;
	}
    }

    void sort_edges(int start, int end) {
	if (start >= end)
	    return;

	int part = quicksort(start, end);
	sort_edges(start,part - 1);
        sort_edges(part + 1, end);
    }

    int quicksort(int s, int e) {
	int k = s - 1;
	int l = s;

	while (l < e) {
	    if (edges[l].w < edges[e].w) {
		k += 1;
		edge ed = edges[k];
		edges[k] = edges[l];
		edges[l] = ed;		
	    }
	    l += 1;
	}
	
	k += 1;
	edge ed = edges[k];
	edges[k] = edges[l];
	edges[l] = ed;
	return k;
    }

    void make_set(int i, vector<int> &parent) {
	parent[i] = i;
    }

    int find_set(int i, vector<int> &parent) {
	if (i == parent[i]) {
	    return i;
	}
	parent[i] = find_set(parent[i], parent);
	return parent[i];
    }

    void union_sets(int a, int b, vector<int> &parent) {
	a = find_set(a, parent);
	b = find_set(b, parent);
	if (a != b) {
	    parent[b] = a;
	}
    }
    
    void kruskal() {
	sort_edges(0, edges.size() - 1);
	vector<int> parent(vertices);
	for (int i = 1; i <= vertices; i++) {
	    make_set(i, parent);
	}

	int total = 0;
	for (int i = 0; i < edges.size(); i++) {
	    edge e = edges[i];
	    int a = find_set(e.u, parent);
	    int b = find_set(e.v, parent);
	    if (a != b) {
		total += e.w;
		union_sets(a, b, parent);
	    }
	}

	cout << total << endl;
    }
};

int main () {
    int vertices, edges;
    cin >> vertices >> edges;

    graph g(vertices);
    int u, v, w;
    for (int i = 0; i < edges; i++) {
	cin >> u >> v >> w;
	g.add_edge(u, v, w);
    }
    g.kruskal();
}
