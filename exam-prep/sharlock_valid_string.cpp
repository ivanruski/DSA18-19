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
    vector<int> occ;
    for (int i = 0; i < 26; i++) {
	if (arr[i] != 0) {
	    occ.push_back(arr[i]);
	}
    }

    map<int, int> count;
    for (int i = 0; i < occ.size(); i++) {
	if (count.find(occ[i]) == count.end()) {
	    count.insert({occ[i], 1});
	}
	else {
	    count[occ[i]] += 1;
	}
    }

    if (count.size() == 1) {
	cout << "YES\n";
    }
    else if (count.size() > 2) {
	cout << "NO\n";
    }
    else {
	auto it = count.begin();
	int a = it->first;
	int ac = it->second;
	it++;
	int b = it->first;
	int bc = it->second;
	if (bc == 1 && b == a + 1) {
	    cout << "YES\n";
	}
	else if (ac == 1 && a == 1) {
	    cout << "YES\n";
	}
	else {
	    cout << "NO\n";
	}
    }
    
    for (auto it : count) {
	//cout << it.first << " " << it.second << endl;
    }
}
