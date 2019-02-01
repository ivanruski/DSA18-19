#include <iostream>
#include <math.h>

using namespace std;

int main () {
    int n, k, j;
    cin >> n;
    int *tree = new int[n + 1];
    tree[1] = -1;
    for (int i = 1; i < n; i++){
	cin >> k >> j;
	if (tree[k] != 0) {
	    tree[j] = k;
	}
	else {
	    tree[k] = j;
	}
    }

    // for (int i = 1; i < n + 1; i++) {
    // 	cout << tree[i] << " ";
    // }
    // cout << endl;

    cin >> n;
    for (int i = 0; i < n; i++) {
	cin >> k >> j;
	if (j == 0) {
	    cout << k << endl;
	}
	else {
	    int p = tree[k] / j;
	    cout << p << endl;
	}
    }
}
