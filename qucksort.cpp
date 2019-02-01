#include <iostream>
#include <vector>
using namespace std;

vector<int> nums;

void sort(int start, int end) {
    if (start >= end)
	return;

    int part = quicksort(start, end);
    sort_edges(start,part - 1);
    sort_edges(part + 1, end);
}

int quicksort(int s, int e) {
    int k = s - 1;
    int l = s;

    while (l < e) {
	if (nums[l] < nums) {
	    k += 1;
	    edge ed = edges[k];
	    edges[k] = edges[l];
	    edges[l] = ed;		
	}
	l += 1;
    }
	
    k += 1;
    edge ed = edges[k];
    edges[k] = edges[l];
    edges[l] = ed;
    return k;
}

int main () {
    int n;
}
