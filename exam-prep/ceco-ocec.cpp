#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

int get_price(vector<int> &a, vector<int> &b) {
    int min = 27;
    int min_index;
    for (int i = 0; i < b.size(); i++) {	
	if (a[0] < b[i]) {
	    int tmp = b[i] - a[0];
	    if (tmp < min) {
		min = tmp;
		min_index = i;
	    }
	}
	else {
	    int tmp = (26 - a[0]) + b[i];
	    if (tmp < min) {
		min = tmp;
		min_index = i;
	    }
	}
    }

    // cout << "a : " << a[0] << " ";
    // cout << "b : " << b[min_index] << " ";
    // cout << " min: " << min << endl;
    a.erase(a.begin() + 0);
    b.erase(b.begin() + min_index);

    return min;
}

void remove_dup(map<int,int> &a, map<int, int> &b) {
    for (auto it : a) {
	int letter = it.first;
	int count = it.second;
        if (b.find(letter) != b.end()) {
	    if (a[letter] >= b[letter]) {
		a[letter] -= b[letter];
		b[letter] = 0;
	    }
	    else {
		b[letter] -= a[letter];
		a[letter] = 0;
	    }
	}
    }
}

int main () {
    int tests;
    cin >> tests;

    for (int t = 0; t < tests; t++) {
	string wa, wb;
	cin >> wa >> wb;

	int size = wa.length();
	map<int, int> a;
	map<int, int> b;

	for (int i = 0; i < size; i++) {
	    int li = wa[i] - 'A' + 1;
	    if (a.find(li) == a.end()) {
		a.insert({li, 1});
	    }
	    else {
		a[li] += 1;
	    }
	}

	for (int i = 0; i < size; i++) {
	    int li = wb[i] - 'A' + 1;
	    if (b.find(li) == b.end()) {
		b.insert({li, 1});
	    }
	    else {
		b[li] += 1;
	    }
	}

	remove_dup(a, b);

        vector<int> arr;
	for (auto it : a) {
	    for (int i = 0; i < it.second; i++) {
		arr.push_back(it.first);
	    }
	}

	vector<int> brr;
	for (auto it : b) {
	    for (int i = 0; i < it.second; i++) {
		brr.push_back(it.first);
	    }
	}
	
	int p = 0;
	int i = 0;
	while (arr.empty() == false) {
	    p += get_price(arr, brr);
	}
	cout << p << endl;
    }
}
