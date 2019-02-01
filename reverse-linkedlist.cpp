#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
};

void print(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;

    node *head = new node();
    head->data = n;
    node *in;
    for (int i = n - 1; i > 0; i--) {
	in = new node();
	in->data = i;
	in->next = head;
	head = in;
    }

    node *traverse = head;
    while (traverse != nullptr) {
	cout << traverse->data << " ";
	traverse = traverse->next;
    }
    cout << endl;
    node* prev = nullptr;
    node* curr = head;
    node* next = head->next;

    while (next != nullptr) {
	curr->next = prev;
	prev = curr;
	curr = next;
	next = next->next;
    }
    curr->next = prev;
    
    while (curr != nullptr) {
	cout << curr->data << " ";
	curr = curr->next;
    }
    
    cout << endl;
}
