#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <map>
#include <queue>
using namespace std;

enum color { black, white };

struct edge; 

struct vertex {
    int key;
    vector<edge*> edges;
    color c;
    unsigned long long d;
    vertex (int k) {
        key = k;
        c = white;
        d = ULLONG_MAX;
    }
};

struct edge {
    vertex* to;
    unsigned long long w;
    edge (vertex* t, unsigned long long ww) {
        to = t;
        w = ww;
    }
};

class graph {
public:
    map<int, vertex*> vertices;
    
    void add_vertex (int n) {
        vertex *v = new vertex(n);
        vertices.insert(pair<int, vertex*>(n, v));
    }
    
    void add_edge(int u, int v, unsigned long long w) {
        vertex* uu = find(u);
        vertex* vv = find(v);
        
        uu->edges.push_back(new edge(vv, w));
        vv->edges.push_back(new edge(uu, w));
    }
    
    vertex* find(int u) {
        vertex *uu = nullptr;
        auto it = vertices.find(u);
        if (it != vertices.end()) {
            uu = it->second;
        }
        
        return uu;
    }
    
    void dijkstra (int vv) {
        priority_queue<pair<unsigned long long, vertex*>,
                       vector<pair<unsigned long long, vertex*>>,
                       greater<pair<unsigned long long, vertex*>>> q;
        
        vertex* start = find(vv);
        start->d = 0;
        q.push({0, start});
        
        while (q.empty() == false) {
            vertex *v = q.top().second;
            unsigned long long v_d = q.top().first;
            q.pop();
            if (v->d != v_d) continue;
            
            for (int i = 0; i < v->edges.size(); i++) {
                vertex *to = v->edges[i]->to;
                unsigned long long w = v->edges[i]->w;
                
                 
                if (to->c == white && to->d > v->d + w) {
                    
                    to->d = v->d + w;
                    q.push({to->d, to});
                }
            }
            
            v->c = black;
        }
        
        for (auto it : vertices) {
	    if (it.first == vv) continue;
	    if (it.second->d == ULLONG_MAX)
		cout << "-1 ";
	    else
		cout << it.second->d << " ";
        }
        cout << endl;
    }

    void print () {
	for (auto it : vertices) {
	    if (it.first == 0) {
		continue;
	    }
	    
	    cout << "Vertex: " << it.second->key << endl;
	    for (int i = 0; i < it.second->edges.size(); i++) {
		edge* e = it.second->edges[i];
		cout << "\t" << e->to->key << " " << e->w << endl;
	    }
	    cout << endl;
	}
    }
};

int main() {

    ios_base::sync_with_stdio(false);
    int vertices, edges;
    cin >> vertices >> edges;    
    graph g;
    for (int i = 1;i <= vertices; i++) {
        g.add_vertex(i);
    }
    
    int u, v;
    unsigned long long w;
    for (int i = 0;i < edges; i++) {
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    int vv;
    cin >> vv;
    //g.print();
    g.dijkstra(vv);
    return 0;
}
















