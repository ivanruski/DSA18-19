#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct graph {
    int _v;
    int _e;
    vector<vector<int> > adj;

    graph (int v, int e) {
	adj = vector<vector<int> >(v, vector<int>(e, 0));
	this->_v = v;
	this->_e = e;
    }

    void max_connected_region() {
	int max = 0;
	int *connected = new int(0);
	vector<vector<bool> > visited(_v, vector<bool>(_e, false));
	for (int i = 0; i < _v; i++) {
	    for (int j = 0; j < _e; j++) {
		int conn = connected_cells(visited, i, j);
		if (max < conn) {
		    max = conn;
		}
	    }
	}

	cout << max << endl;
    }

    int connected_cells(vector<vector<bool> > &visited, int r, int c) {
	if (adj[r][c] == 0) {
	    return 0;
	}
	visited[r][c] = true;
	int connected = 1;
	for (int i = -1; i < 2; i++) {
	    for (int j = -1; j < 2; j++) {
		if (is_valid_cell(i + r, j + c)) {

		    if (visited[i + r][j + c] == false) {
			connected += connected_cells(visited, i+r, j+c);
		    }
		}
	    }
	}

	return connected;
    }


    bool is_valid_cell(int i, int j) {
	return i >=0 && i < _v &&
	    j >= 0 && j < _e;	   
    }
};

int main () {
    int v,e;
    cin >> v >> e;
    graph g(v,e);

    for (int i = 0; i < v; i++) {
	for (int j = 0; j < e; j++) {
	    int value;
	    cin >> value;
	    g.adj[i][j] = value;
	}
    }
    g.max_connected_region();
}
    
