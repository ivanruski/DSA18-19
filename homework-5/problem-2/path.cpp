#include <stack>
#include <string>
#include <inttypes.h>
#include <iostream>

using namespace std;

void print_path (stack<int64_t> path) {
    stack<int64_t> copy;
    while (path.empty() == false) {
        copy.push(path.top());
        path.pop();
    }

    while (copy.empty() == false) {
        cout << copy.top() << " ";
        copy.pop();
    }
}

void blue_stone (stack<int64_t> &path, int k) {
    int max = -2147483648;
    int64_t top;
    while (k > 0 && path.empty() == false) {
        top = path.top(); path.pop();
        if (max < top) {
            max = top;
        }
        k--;
    }
    path.push(max);
}

void green_stone (stack<int64_t> &path, int k) {
    int64_t sum = 0;
    int top;
    while (k > 0 && path.empty() == false) {
        top = path.top(); path.pop();
        sum += top;
        k--;
    }
    path.push(sum);
}

int main() {
    int n;
    cin >> n;
 
    string stone_color;
    int stone_value;
    stack<int64_t> path;
    for (int i = 0; i < n ; i++) {
        cin >> stone_color;
        cin >> stone_value;
        if (stone_color == "white") {
            path.push(stone_value);
        }
        else if (stone_color == "blue") {
            blue_stone(path, stone_value);
        }
        else {
            green_stone(path, stone_value);
        }
    }
    print_path(path);
    cout << endl;
}