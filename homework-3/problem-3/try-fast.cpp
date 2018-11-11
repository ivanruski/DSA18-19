#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void fill_arr(vector<int> &arr) {
    int num;
    for (int i = 0; i < arr.size(); i++) {
        cin >> num;
        arr[i] = num;
    }
}

void print(vector<int> &arr) {
    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int quotient(int n, int k) {
    return n/k;
}

int main () {
    int n, k;

    cin >> n; 
    cin >> k;
    vector<int> arr(n);
    fill_arr(arr);
    sort(arr.begin(), arr.end());
    
    int steps = 0;
    int last = arr.size() - 1;

    while(arr[last - 1] - steps > 0) {
        if (last == 0) {
        arr[last] -= steps;
    }

    cout << steps << endl;
}