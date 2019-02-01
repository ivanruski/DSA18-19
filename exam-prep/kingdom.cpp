#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

int main () {
    string j, s;
    cin >> j >> s;

    unordered_set<char> store;
    for (int i = 0; i < j.length(); i++) {
	store.insert(j[i]);
    }

    int total = 0;
    for (int i = 0; i < s.length(); i++) {
        if (store.find(s[i]) != store.end()) {
	    total += 1;
	}
    }

    cout << total << endl;
}
