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

bool all_dry(vector<int> &arr) {
    for(int i = 0; i < arr.size(); i++) {
        if (arr[i] > 0)
            return false;
    }

    return true;
}

void print(vector<int> &arr) {
    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void decrement(vector<int> &arr) {
    for(size_t i = 0; i < arr.size() - 1; i++){
        arr[i] -= 1;
    }
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
    while(arr[last] > 0) {
        arr[last] -= k;
        decrement(arr);
        int i = last - 1;
        int num = arr[last];

        while (i >= 0 && arr[i] > num && arr[i] > 0) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = num;
        steps++;
    }

    cout << steps << endl;
}