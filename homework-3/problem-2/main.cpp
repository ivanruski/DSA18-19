#include <vector>
#include <iostream>
#include <algorithm>
#include <inttypes.h>

using namespace std;

int last_occurence_index(vector<uint32_t>& arr, int left, int right, uint32_t key) {
    if (left > right) return - 1;

    int mid = (right + left) / 2;
  
    if (arr[mid] == key && mid == arr.size() - 1 || mid < arr.size() - 1 && arr[mid] == key && arr[mid + 1] != key) {
        return mid + 1;
    }
    else if (arr[mid] <= key) {
        return last_occurence_index(arr, mid + 1, right, key);
    }
    
    return last_occurence_index(arr, left, mid - 1, key);
}

int first_occurence_index(vector<uint32_t>& arr, int left, int right, uint32_t key) {
    if (left > right) return - 1;

    int mid = (right + left) / 2;
  
    if (arr[mid] == key && mid == 0 || mid > 0 && arr[mid] == key && arr[mid-1] != key) {
        return mid + 1;
    }
    else if (arr[mid] < key) {
        return first_occurence_index(arr, mid + 1, right, key);
    }
    
    return first_occurence_index(arr, left, mid - 1, key);
}

void print_arr(vector<uint32_t> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void fill_arr(vector<uint32_t> &arr) {
    uint32_t input;
    for (int i = 0; i < arr.size(); i++) {
        cin >> input;
        arr[i] = input;
    }
}
int main () {
    int n;
    cin >> n;
    vector<uint32_t> arr(n);
    fill_arr(arr);
    sort(arr.begin(), arr.end());
    int q;
    cin >> q;
    while (q > 0) {
        uint32_t key;
        cin >> key;
        cout << first_occurence_index(arr, 0, n - 1, key) << " " << last_occurence_index(arr, 0, n - 1, key) << endl;
        q--;
    }
}
