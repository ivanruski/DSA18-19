#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

int main () {
    string s;
    cin >> s;
    vector<int> arr(26, 0);
    for (int i = 0; i < s.length(); i++) {
	int ci = s[i] - 'a';
	arr[ci] += 1;
    }

    map<int, vector<int>, greater<int> > m;
    for (int i = 0; i < 26; i++) {
	if (arr[i] != 0) {
	    if (m.find(arr[i]) == m.end()) {
		vector<int> v;
		v.push_back(i);
		m.insert({arr[i], v});
	    }
	    else {
		m[arr[i]].push_back(i);
	    }
	}
    }

    for (auto it : m) {
	int count = it.first;
	vector<int> letters = it.second;
	for (int i = 0; i < letters.size(); i++) {
	    for (int j = 0; j < count; j++) {
		cout << (char)(letters[i] + 'a');
	    }
	}
    }
    cout << endl;
}
