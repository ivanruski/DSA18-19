#include <vector>
#include <iostream>

using namespace std;
enum color { white, gray, black };
struct edge;
struct vertex {
    int key;
    color c;
    bool l_dest;
    vector<edge> edges;

    vertex (int k) {
	key = k;
	c = white;
	l_dest = false;
    }
};

struct edge {
    vertex *to;
    int w;
    edge (vertex *v, int wght) {
	to = v;
	w = wght;
    }
};

struct graph {
    vector<vertex*> vertices;
    vector<int> dest;
    
    graph (int vs) {
	for (int i = 0; i <= vs; i++) {
	    vertices.push_back(new vertex(i));
	}
    }

    void add_letter_dest(int v) {
	vertices[v]->l_dest = true;
	dest.push_back(v);
    }

    void add_edge (int u, int v, int w) {
	vertex *uu = vertices[u];
	vertex *vv = vertices[v];

	uu->edges.push_back({vv, w});
	vv->edges.push_back({uu, w});
    }

    void best_route () {
	vertex *s = vertices[dest[0]];
	int delivered = 0;
	int distance = 0;
    }

    void dfs(vertex *v,
	     int &distance,
	     int &delivered) {
	if (v->l_dest) {
	    delivered += 1;
	    if (delivered == dest.size()) {
		
	    }
	}
        
	for (int i = 0; i < v->edges.size(); i++) {
	    edge e = v->edges[i];

	    //dfs
	}
    }
};

int main () {
    int vertices, letters;
    cin >> vertices >> letters;
    graph g(vertices);

    int letter_to;
    for (int i = 0; i < letters; i++) {
	cin >> letter_to;
	g.add_letter_dest(letter_to);
    }

    int u,v,w;
    for (int i = 0; i < vertices - 1; i++) {
	cin >> u >> v >> w;
	g.add_edge(u, v, w);
    }

    g.best_route();
}
