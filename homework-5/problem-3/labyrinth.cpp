#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h> 

using namespace std;

struct node {
    int r;
    int c;
    node (int r, int c) {
	this->r = r;
	this->c = c;
    }
};

bool nodes_equals(node *current, node *destination) {
    return current->r == destination->r &&
	current->c == destination->c;
}

int **create_labyrinth(int m, int n) {
    int **l = new int*[m];
    for (int i = 0; i < m; i++) {
        l[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> l[i][j];
        }
    }

    return l;
}

int **create_distance_matrix(int m, int n) {
    int **l = new int*[m];
    for (int i = 0; i < m; i++) {
        l[i] = new int[n];
	for (int j = 0; j < n; j++) {
	    l[i][j] = -1;
	}
    }
    return l;
}

int **distance_matrix(int m, int n, int **matrix) {
    bool visited[m][n];
    memset(visited, false, sizeof visited);

    int **distance_matrix = create_distance_matrix(m, n);
    node sentinel(-2, -2);
    queue<node> q;
    q.push(node(0,0));
    q.push(sentinel);
    int distance = 1;
    distance_matrix[0][0] = 0;
    visited[0][0] = true;
    
    while (q.empty() == false) {
	node current = q.front(); q.pop();
	if (nodes_equals(&current, &sentinel)) {
	    distance += 1;

	    if (q.empty() == true) {
		break;
	    }
	    q.push(sentinel);
	    continue;
	}

	for (int row = -1; row < 2; row += 2) {
	    if (current.r + row > -1 && current.r + row < m &&
       	        visited[current.r + row][current.c] == false &&
		matrix[current.r + row][current.c] != 1) {

		 q.push(node(current.r + row, current.c));
	         visited[current.r + row][current.c] = true;
		 distance_matrix[current.r + row][current.c] = distance;
	    }    
	}   

	for (int col = -1; col < 2; col += 2) {
	    if (current.c + col > -1 && current.c + col < n &&
	        visited[current.r][current.c + col] == false &&
	        matrix[current.r][current.c + col] != 1) {

		q.push(node(current.r, current.c + col));
		visited[current.r][current.c + col] = true;
		distance_matrix[current.r][current.c + col] = distance;
	    }   
	}   
    }

    return distance_matrix;
}

node* get_destination() {
    node* dest = new node(0,0);
    cin >> dest->r;
    cin >> dest->c;
    return dest;
}

int main () {
    int m,n,k;
    cin >> m >> n >> k;
    int **matrix = create_labyrinth(m, n);
    int **distanc_matrix = distance_matrix(m, n, matrix);
    
    while (k > 0) {
	node* dest = get_destination();

	if (matrix[dest->r][dest->c] == 1) {
	    cout << "-1\n";
	}
	else {
	    cout << distanc_matrix[dest->r][dest->c] << endl;
	}
	k -= 1;
    }
}
