#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <limits>

using namespace std;
typedef unsigned long ulong;
const ulong INF = numeric_limits<ulong>::max();

struct edge;

struct vertex {
    int key;
    ulong d;
    vector<edge*> edges;
    
    vertex (int k) {
        key = k;
	d = INF;
    }
};

struct edge {
    vertex *v;
    ulong w;
    edge (vertex* vertx, ulong weight) {
	v = vertx;
	w = weight;
    }
};

class graph {
public:
    map<int, vertex*> vertices;
    
    void add_vertex(int v) {
        vertex *vv = new vertex(v);
	vertices.insert(pair<int,vertex*>(v, vv));
    }
    
    void add_edge(int u, int v, ulong w) {
        vertex *uu = find(u);
        vertex *vv = find(v);
        
        vv->edges.push_back(new edge(uu, w));
        uu->edges.push_back(new edge(vv, w));
    }
    
    vertex* find (int k) {
        vertex* v = nullptr;
        
        auto it = vertices.find(k);
        if (it != vertices.end()) {
            v = it->second;
        }
        
        return v;
    }
    
    void bfs(int vertex) {
        auto start = vertices.find(vertex);
        bfs_vertex(start->second);

        for (auto &pair : vertices) {
	    if (pair.first != vertex) {
		if (pair.second->d == INF) {
		    cout << "-1 ";
		}
		else {
		    cout << pair.second->d << " ";
		}
	    }
	}
    
	cout << endl;
    }
    
    void bfs_vertex (vertex *s) {
	priority_queue<pair<ulong, vertex*>,
		       vector<pair<ulong,vertex*> >,
		       greater<pair<ulong,vertex*> > > q;
	s->d = 0;
	q.push({0, s});

	while (q.empty() == false) {
	    ulong d = q.top().first;
	    vertex *u = q.top().second;
	    q.pop();
        
	    if (u->d != d) 
		continue;
        
	    for (int i = 0; i < u->edges.size(); i++) {
		edge *e = u->edges[i];
        
		if (e->v->d > u->d + e->w) {
		    e->v->d = u->d + e->w;	 
		    q.push({e->v->d, e->v});
		}
	    }
	}
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;

    while (tests > 0) {
	graph g;
	int vertices, edges;
	cin >> vertices >> edges;
	for (int i = 1; i <= vertices; i++) {
	    g.add_vertex(i);
	}
    
	int u,v,w;
	for (int i = 0; i < edges; i++) {
	    cin >> u >> v >> w;
	    g.add_edge(u,v,w);
	}

	int vertex;
	cin >> vertex;
	g.bfs(vertex);
	tests--;
    }
}
