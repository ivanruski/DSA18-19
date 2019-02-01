#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstdint>

using namespace std;
enum color { white, black };
struct edge;

struct vertex {
    int key;
    color c;
    uint64_t d;
    edge *p;
    vector<edge*> edges;
    map<int, edge*> railways;
    
    vertex(int k) {
	key = k;
	c = white;
	p = nullptr;
	d = ULLONG_MAX;
    }
};

struct edge {
    uint64_t w;
    vertex* v;
    bool rail;
    bool from_sp;
    
    edge (uint64_t weight, vertex* to, bool is_rail = false) {
	w = weight;
	v = to;
	rail = is_rail;
	from_sp = false;
    }
};

struct graph {
    map<int, vertex*> vertices;
    int c = 0;

    void add_edge(int u, int v, uint64_t w) {
	vertex* uu = this->find(u);
	vertex* vv = this->find(v);

	if (uu == nullptr) {
	    uu = new vertex(u);
	    vertices.insert({u, uu});
	}
    
	if (vv == nullptr) {
	    vv = new vertex(v);
	    vertices.insert({v, vv});
	}

	uu->edges.push_back(new edge(w, vv));
	vv->edges.push_back(new edge(w, uu));
    }

    void add_railway(int u, uint64_t w) {
	vertex *s = this->find(1);
	vertex *uu = this->find(u);
	auto it = s->railways.find(u);
	if (it == s->railways.end()) {
	    s->railways.insert({u, new edge(w, uu, true)});
	}
	else {
	    if (it->second->w > w) {
		it->second->w = w;
	    }
	    c++;
	}
    }
    
    void find_useless_railways() {
	vertex* s = this->find(1);
	merge_railways_to_edges(s);
	this->dijkstra(s);
    
	for (int i = 0; i < s->edges.size(); i++) {
	    if (s->edges[i]->rail && s->edges[i]->from_sp == false) {
		c++;
	    }
	}

	cout << c << endl;
    }

    void merge_railways_to_edges(vertex *s) {
	for (auto it : s->railways) {
	    s->edges.push_back(it.second);
	}
    }

    void print () {
	for (auto it : vertices) {
	    if (it.first == 0) {
		continue;
	    }
        
	    cout << "Vertex: " << it.second->key
		 << ", Distanse: " << it.second->d << endl;
	    for (int i = 0; i < it.second->edges.size(); i++) {
		edge* e = it.second->edges[i];
		cout << "\t" << e->v->key << " " << e->w << endl;
	    }
	    cout << endl;
	}
    }

private:
    void dijkstra (vertex* s) {
	priority_queue<pair<uint64_t, vertex*>,
		       vector<pair<uint64_t, vertex*>>,
		       greater<pair<uint64_t, vertex*>>> q;

	s->d = 0;
	q.push({0, s});
	while (q.empty() == false) {
	    uint64_t dis = q.top().first;
	    vertex *u = q.top().second;
	    q.pop();

	    if (dis != u->d) continue;
        
	    for (int i = 0; i < u->edges.size(); i++) {
		edge* e = u->edges[i];
		vertex *v = e->v;

		if (v->d > u->d + e->w) {
		    v->d = u->d + e->w;
		    q.push({v->d, v});
		    if (v->p != nullptr) {
			v->p->from_sp = false;
		    }
		    v->p = e;
		}
		else if (v->d == u->d + e->w) {
		    if (v->p->rail == false) {
			continue;
		    }
		    if (e->rail == false) {
			if (v->p != nullptr) {
			    v->p->from_sp = false;
			}
			v->p = e;
		    }
		}
	    }

	    if (u->p != nullptr) {
		u->p->from_sp = true;
	    }
	}
    }
    
    vertex* find(int u) {
	vertex* v = nullptr;
	auto it = vertices.find(u);
	if (it != vertices.end()) {
	    v = it->second;
	}
	return v;
    }

    
};

int main () {
    ios_base::sync_with_stdio(false);
    
    int vertices, edges, railways;
    cin >> vertices >> edges >> railways;
    graph g;
    int u, v;
    uint64_t w;
    for (int i = 0; i < edges; i++) {
	cin >> u >> v >> w;
	g.add_edge(u, v, w);
    }

    for (int i = 0; i < railways; i++) {
	cin >> u >> w;
	g.add_railway(u, w);
    }
    g.find_useless_railways();
    //g.print();
}
