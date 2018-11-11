#include <iostream>
using namespace std;
struct node {
    int data = 0;
    node* next = nullptr;
};

int main() {   
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    node* head = new node();
    head->data = n;

    while (cin >> n) {
        node* nd = new node();
        nd->data = n;
        nd->next = head;
        head = nd;
    }

    int min = 10001;
    int max = -1;
    unsigned long long sum = 0;
    node* curr = head;
    while (curr != nullptr) {
        if (curr->data < min) {
            min = curr->data;
        }
        if (curr->data > max) {
            max = curr->data;
        }

        sum += curr->data;
        curr = curr->next;       
    }
    cout << min << " " << max << " " << sum << endl;

    return 0;
}
