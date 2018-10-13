#include <vector>
#include <iostream>

using namespace std;
static unsigned long long sum = 0;

void parse_input(vector<int> &arr, int n) {
    int tmp;
    for(int i = 0; i < n; i++) {
        cin >> tmp;
        arr.push_back(tmp);
    }
}

void merge(vector<int> &arr, int left, int mid, int right){
    int lsize = mid - left + 1;
    int rsize = right - mid;

    int L[lsize], R[rsize];
    for (int i = 0; i < lsize; i++) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < rsize; i++) {
        R[i] = arr[mid + i + 1];
    }

    int i = 0, j = 0;
    int k = left;

    while (i < lsize && j < rsize) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i += 1;
        }
        else {
            arr[k] = R[j];
            j += 1;
            sum += lsize - i;
        }
        k += 1;
    }

    while (i < lsize) {
        arr[k] = L[i];
        i+= 1;
        k+= 1;
    }

    while (j < rsize) {
        arr[k] = R[j];
        j+= 1;
        k+= 1;
    }
}

void merge_sort(vector<int> &arr, int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    int test_cases;
    cin >> test_cases;

    int n;
    while (test_cases > 0) {
        cin >> n;
        vector<int> nums;
        parse_input(nums, n);
        merge_sort(nums, 0, n - 1);
        cout << sum << endl;

        nums.clear();
        sum = 0;
        test_cases -= 1;
    }

    return 0;
}