#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef long long llong;
const llong NINF = numeric_limits<llong>::min();

struct edge {
    int u;
    int v;
    llong w;
    edge (int u, int v, llong w) {
	this->u = u;
	this->v = v;
	this->w = w;
    }
};

class graph {
public:
    int vertecies;
    vector<edge*> edges;

    graph(int n, int m) {
	vertecies = n;
	//edges = vector<edge*>(m + 1);
    }

    void add_edge(int u, int v, llong w) {
	edge *e = new edge(u, v, w);
	edges.push_back(e);
    }

    void bellman_ford(int s, int t) {
	vector<llong> d(vertecies + 1, NINF);
	d[s] = 0;

	for (int i = 0; i < vertecies; i++) {
	    for (int j = 0; j < edges.size(); j++) {
		if (d[edges[j]->u] != NINF) {
		    if (d[edges[j]->u] + edges[j]->w > d[edges[j]->v]) {
			d[edges[j]->v] = d[edges[j]->u] + edges[j]->w; 
		    }
		}
	    }
	}

	if (d[t] == NINF) {
	    cout << "-1\n";
	}
	else {
	    cout << d[t] << endl;
	}
    }
};

int main () {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    
    graph g(n, m);
    int u,v;
    llong w;
    for (int i = 0; i < m; i++) {
	cin >> u >> v >> w;
	g.add_edge(u, v, w);
    }
    
    g.bellman_ford(s, t);
}
