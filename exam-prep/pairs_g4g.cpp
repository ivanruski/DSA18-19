#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
using namespace std;


int main() {
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        int n;
        cin >> n;
        vector<int> gt_zero;
        vector<int> lt_zero;
	vector<int> zeros;
        int ch;
        for (int j = 0; j < n; j++) {
            cin >> ch;
            if (ch > 0) {
                gt_zero.push_back(ch);
            }
            else if (ch < 0) {
                lt_zero.push_back(ch);
            }
	    else {
		zeros.push_back(0);
	    }
        }
        
        sort(gt_zero.begin(), gt_zero.end(), greater<int>());
        int64_t total = 0;
	if (gt_zero.size() > 0) {
	    if (gt_zero.size() % 2 == 0) {
		for (int i = 0; i < gt_zero.size(); i+= 2) {
		    if (gt_zero[i] == 1 || gt_zero[i + 1] == 1) {
			total += gt_zero[i] + gt_zero[i + 1];
		    }
		    else {
			total += (gt_zero[i] * gt_zero[i+1]);
		    }
		}
            
	    } else {
		for (int i = 0; i < gt_zero.size() - 1; i+= 2) {
		    if (gt_zero[i] == 1 || gt_zero[i + 1] == 1) {
			total += gt_zero[i] + gt_zero[i + 1];
		    }
		    else {
			total += (gt_zero[i] * gt_zero[i+1]);
		    }
		}
		total += gt_zero[gt_zero.size()-1];
	    }
	}
        
        sort(lt_zero.begin(), lt_zero.end());
        if (lt_zero.size() > 0) {	    
	    if (lt_zero.size() % 2 == 0) {
		for (int i = 0; i < lt_zero.size(); i+= 2) {
		    total += (lt_zero[i] * lt_zero[i+1]);
		}
	    } else {
		for (int i = 0; i < lt_zero.size() - 1; i+= 2) {
		    total += (lt_zero[i] * lt_zero[i+1]);
            
		}
		if (zeros.size() == 0) {
		    total += lt_zero[lt_zero.size() -1];
		}
	    }
	}
        
        cout << total << endl;
        
    }
    return 0;
}
