#include <iostream>
#include <vector>

using namespace std;

void parse_input(vector<int> &arr, int n) {
    int tmp;
    for(int i = 0; i < n; i++) {
        cin >> tmp;
        arr.push_back(tmp);
    }
}

void swap (vector<int> &arr, int left, int right) {
    if (left == right) return;
    int tmp = arr[left]; 
    arr[left] = arr[right];
    arr[right] = tmp;
}

int partition(vector<int> &arr, int left, int right) {
    int l = left - 1;
    int k = left;
    while (k < right) {
        if (arr[k] < arr[right]) {
            swap(arr, l + 1, k);
            l += 1;
        }
        k += 1;
    }
    swap(arr, l + 1, right);
    return l + 1;
}

void quick_sort(vector<int> &arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = partition(arr, left, right);
    quick_sort(arr, left, mid - 1);
    quick_sort(arr, mid + 1, right);
}

int main () {
    int n; 
    cin >> n;
    int k;
    cin >> k;

    vector<int> arr;

    parse_input(arr, n);
    quick_sort(arr, 0, n - 1);
    
    int max = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        if (sum <= k) {
            max += 1;
            continue;
        }
        else {
            break;
        }
    }

    cout << max << endl;
    
}