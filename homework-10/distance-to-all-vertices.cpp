#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

enum color { white, gray, black };

struct vertex {
    int key;
    int d;
    color c;
    vector<vertex*> edges;
    
    vertex (int k) {
        key = k;
	d = -1;
        c = white;
    }
};

class graph {
    public:
    vertex *store;
    map<int, vertex*> vertices;
    

    void add_vertex(int v) {
        vertex *vv = new vertex(v);
	vertices.insert(pair<int,vertex*>(v, vv));
    }
    
    void add_edge(int u, int v) {
        vertex *uu = find(u);
        vertex *vv = find(v);
        
        vv->edges.push_back(uu);
        uu->edges.push_back(vv);
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
		cout << pair.second->d << " ";
	    }
	}
	
	cout << endl;
    }
    
    void bfs_vertex (vertex *v) {
        vertex *nil = new vertex(-123);
        v->c = gray;
        queue<vertex*> q;
        q.push(v);
        q.push(nil);
        
        int d = 6;
        while (q.empty() == false) {
            vertex *c = q.front(); q.pop();
            if (c == nil) {
                d += 6;
                
                if (q.empty() == false) {
                    q.push(nil);
                }
                continue;
            }
            
            for (size_t i = 0; i < c->edges.size(); i++) {
                if (c->edges[i]->c == white) {
                    c->edges[i]->c = gray;
		    c->edges[i]->d = d;
		    q.push(c->edges[i]);
                    
                }
            }
            c->c = black;
        }
    }
};

int main() {
    int tests;
    cin >> tests;

    while (tests > 0) {
	graph g;
	int vertices, edges;
	cin >> vertices >> edges;
	for (int i = 1; i <= vertices; i++) {
	    g.add_vertex(i);
	}
	
	int u,v;
	for (int i = 0; i < edges; i++) {
	    cin >> u >> v;
	    g.add_edge(u,v);
	}

	int vertex;
	cin >> vertex;
	g.bfs(vertex);
	tests--;
    }
}
