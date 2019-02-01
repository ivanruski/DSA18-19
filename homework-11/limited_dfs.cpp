#include <vector>
#include <stack>
#include <iostream>
#include <map>
using namespace std;

enum color { black, gray, white };
struct edge;

struct vertex {
    int u;
    color c;
    vector<edge*> edges;
    
    vertex(int u) {
        this->u = u;
        this->c = white;
    }
};

struct edge {
    int v;
    int w;
    edge (int to, int we) {
        v = to;
        w = we;
    }
};

class graph {
public:
    vector<vertex*> vertices;
    int vCount;
    map<int, int> m;
    
    graph(int vs) {
        vCount = vs;
        
        for (int i = 0; i <= vCount; i++) {
            vertices.push_back(new vertex(i));
        }
    }
    
    void add_edge (int u, int v, int w) {
        vertex *uu = vertices[u];
        uu->edges.push_back(new edge(v, w));
    }
    
    void find_path(int k) {
        for (int i = 1; i < vertices.size(); i++) {
            vertex *v = vertices[i];
            vector<bool> visited(vertices.size(), false);
            limited_dfs(v, k, 0, visited);
        }
        
        int max = -1;
        int total = -1;
        
        for (auto it : m) {
	    if (total < it.second && it.first != -1) {
		max = it.first;
		total = it.second;
	    }
	    else if (it.second == total && max < it.first) {
		max = it.first;
		total = it.second;
	    }
	    //cout << it.second << " " << it.first << endl;
        }
        
        cout << max << endl;
    }
    
    void limited_dfs (vertex *v, int limit, int distance, vector<bool> visited) {
        if (limit == 0) {
	    if (m.find(distance) == m.end()) {
                    m.insert({distance, 1});
                }
                else {
                    m[distance] += 1;
            }
            return;
        }

	if (visited[v->u]) {
	    return;
	}
	else {
	    visited[v->u] = true;
	}
	
        for (int i = 0; i < v->edges.size(); i++) {
            edge *e = v->edges[i];
            if (visited[e->v]) {
                continue;
            }
            
            vertex *uu = vertices[e->v];
            limited_dfs(uu, limit - 1, distance + e->w, visited);
        }
    }
    
};

int main() {
    ios_base::sync_with_stdio(false);
    int vs, e;
    cin >> vs >> e;
    
    graph g(vs);
    
    int u, v, w;
    for (int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
    int k;
    cin >> k;
    g.find_path(k);
    return 0;
}

