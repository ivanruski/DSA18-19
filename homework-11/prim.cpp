#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <climits>
#include <cstdint>
using namespace std;
enum color { black, white };
struct edge;

struct vertex {
    int key;
    color c;
    vector<edge*> edges;

    vertex(int k) {
	key = k;
	c = white;
    }
};

struct edge {
    vertex *v;
    uint32_t w;

    edge (vertex *vrtx, uint32_t weight) {
	v = vrtx;
	w = weight;
    }
};

class graph {
public:
    vertex* nil;
    vector<vertex*> vertices;

    graph (int vrtices) {
	nil = new vertex(-1);
	for (int i = 0; i <= vrtices; i++) {
	    vertices.push_back(nil);
	}
    }

    void add_edge(int u, int v, uint32_t w) {
	vertex *uu = vertices[u];
	vertex *vv = vertices[v];

	if (uu == nil) {
	    vertices[u] = new vertex(u);
	    uu = vertices[u];
	}
	if (vv == nil) {
	    vertices[v] = new vertex(v);
	    vv = vertices[v];
	}

	uu->edges.push_back(new edge(vv, w));
	vv->edges.push_back(new edge(uu, w));
    }

    void prim(int start) {
	priority_queue<pair<int, edge*>,
		       vector<pair<int, edge*> >,
		       greater<pair<int, edge*> > > q;

	vertex *u = vertices[start];
	for (int i = 0; i < u->edges.size(); i++) {
	    q.push({u->edges[i]->w,u->edges[i]});
	}

	u->c = black;
	int total = 0;
	while (q.empty() == false) {
	    edge *e = q.top().second;
	    q.pop();
	    
	    if (e->v->c == black)
		continue;
	    
	    total += e->w;
	    vertex *v = e->v;
	    for (int i = 0; i < v->edges.size(); i++) {
		if (v->edges[i]->v->c == white) {
		    q.push({v->edges[i]->w, v->edges[i]});
		}
	    }

	    v->c = black;
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
    int s = 1;
    //cin >> s;
    g.prim(s);
}


