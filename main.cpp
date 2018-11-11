#include <iostream>
using namespace std;

void fill_arr(int *arr, int n){
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

void merge(int *arr, int left, int mid, int right) {
    int lsize = mid - left + 1;
    int larr[lsize];
    for (int i = 0; i < lsize; i++) {
        larr[i] = arr[i + left];
    }
    int rsize = right- mid;
    int rarr[rsize];
    for (int i = 0; i < rsize; i++) {
        rarr[i] = arr[i + mid + 1];
    }
    
    int i = 0;
    int k = 0;
    int l = left;
    
    while (i < lsize && k < rsize){
        if (larr[i] < rarr[k]) {
            arr[l] = larr[i];
            i++;
        }
        else {
            arr[l] = rarr[k];
            k++;
        }
        l++;
    }
    
    while (i < lsize) {
        arr[l] = larr[i];
        i++;
        l++;
    }
    
    while (k < rsize) {
        arr[l] = rarr[k];
        k++;
        l++;
    }
}

void mergesort(int *arr, int left, int right) {
    if (left >= right){
        return;
    }
    
    int mid = left + (right - left) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void print(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int binary_search(int *arr, int left, int right, int key, int isnot) {
    if (left > right) return -1;

    int mid = (left + right)  / 2;
    if (arr[mid] == key && mid != isnot) { 
        return mid;
    }
    else if (arr[mid] > key) {
        return binary_search(arr, left, mid - 1, key, isnot);
    }
    else {
        return binary_search(arr, mid + 1, right, key, isnot);
    }
}

int main() {
	int tests;
	cin >> tests;
	
	for (int i = 0; i < tests; i++) {
	    int n;
	    int sum;
	    cin >> n >> sum;
	    int arr[n];
	    fill_arr(arr, n);
	    mergesort(arr, 0, n - 1);

        bool yes = false;
        for(int i = 0; i < n; i++) {
            int key = sum - arr[i];
            if (binary_search(arr, 0 , n - 1, key, i) != -1) {
                yes = true;
                break;
            }
        }
        
        if (yes) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
	}
}