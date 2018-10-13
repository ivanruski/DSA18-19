#include <iostream>
#include <string>

using namespace std;

void parse_input(int *result) {
        char buff[500];
        int i = 0;

        cin.getline(buff,500); 
        while (buff[i] != '\0') {
            result[buff[i] - 'a'] += 1;
            i++;
        }
}

void sort (int *arr, int size) {
    int smaller;
    for (int i = 0; i < size; i++) {
        smaller = i;
        for (int k = i + 1; k < size; k++) {
            if (arr[k] < arr[smaller])
                smaller = k;
        }
        int tmp = arr[smaller];
        arr[smaller] = arr[i];
        arr[i] = tmp;
    }
}

int begining(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] != 0) {
            return i;
        }   
    }
    return size;
}

int abs(int a) {
    if (a < 0)
        return -a;
    return a;
}

int main() {
    int *alphabet = new int[26] {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    parse_input(alphabet);
    sort(alphabet, 26);
    int end = 25;
    int start = begining(alphabet, 26);

    while (start < end) {
        alphabet[end - 1] = abs(alphabet[end] - alphabet[end - 1]);
        end = end - 1;
    }

    if (alphabet[start] <= 1)
        cout << "Yes" << endl;
    else 
        cout << "No" << endl;
    
}