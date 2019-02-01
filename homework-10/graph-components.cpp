i3l#include <iostream>
#include <vector>
#include <queue>

using std::queue;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

enum color { white, gray, black };

struct vertex {
    color c;
    int key;
    vector<vertex*> edges;

    vertex (int k) {
	key = k;
    }
};

class graph {
private:
    vector<vertex*> vertices;

public:
    graph() {
	
    }

    bool add_vertex(int key) {
	if (find(key) == nullptr)
	    return false;

	vertex *v = new vertex(key);
	vertices.push_back(v);
	return true;
    }

    bool add_edge (int u, int v) {
	vertex *uu = find(u);
	vertex *vv = find(v);

	if (uu == nullptr) {
	    uu = new vertex(u);
	    vertices.push_back(uu);
	}
	if (vv == nullptr) {
	    vv = new vertex(v);
	    vertices.push_back(vv);
	}

	uu->edges.push_back(vv);
	vv->edges.push_back(uu);
	return true;
    }

    vertex* find(int key) {
	vertex *v = nullptr;

	for (size_t i = 0; i < vertices.size(); i++) {
	    if (vertices[i]->key == key) {
		v = vertices[i];
		break;
	    }
	}
	
	return v;
    }

    void bfs () {
	for (size_t i = 0; i < vertices.size(); i++) {
	    vertices[i]->c = white;
	}
	
	int min = 32556;
	int max = -1;

	for (size_t i = 0; i < vertices.size(); i++) {
	    if (vertices[i]->c != white)
		continue;
	    
	    int connected = bfs_connected(vertices[i]);
	    if (connected > max)
		max = connected;
	    if (connected < min)
		min = connected;
	}

	cout << min << " " << max << endl;
    }

    int bfs_connected(vertex *v) {
	int count = 1;
	
	v->c = gray;
	queue<vertex*> q;
	q.push(v);

	while (q.empty() == false) {
	    vertex *c = q.front(); q.pop();

	    for (size_t i = 0; i < c->edges.size(); i++) {
		if (c->edges[i]->c == white) {
		    count++;
		    c->edges[i]->c = gray;
		    q.push(c->edges[i]);
		}
	    }

	    c->c = black;
	}

	return count;
    }
};

int main () {
    graph g;
    int n;
    cin >> n;

    int u,v;
    for (int i = 0; i < n; i++) {
	cin >> u >> v;
	g.add_edge(u,v);
    }

    g.bfs();
}
    

    
    
