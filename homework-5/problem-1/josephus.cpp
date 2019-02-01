#include <iostream>

using namespace std;

struct node {
    int i;
    node* next;
};

node* init_for_n_even(int n) {
    node* head = new node();
    head->i = 1;
    
    node *tail = new node();
    tail->i = n - 1;
    tail->next = head;
    
    for (int i = n-2; i > 2; i -= 2) {
        node *k = new node();
        k->i = i - 1;
        k->next = tail;
        tail = k;
    }
    head->next = tail;
    return head;
}

node* init_for_n_odd(int n) {
    
    node *current_tail = new node();
    current_tail->i = n;
    
    node *real_tail = current_tail;

    for (int i = n - 2; i >= 1; i -= 2) {
        node *k = new node();
        k->i = i;
        k->next = current_tail;
        current_tail = k;
    }
    real_tail->next = current_tail;

    return real_tail;
}

bool isEven(int n){
    return n % 2 == 0;
}

int main()
{
    int n;
    cin >> n;
    node *head;
    if (isEven(n)) {
        head = init_for_n_even(n);
    }
    else {
        head = init_for_n_odd(n);
    }

    while (head != head->next) {
        head->next = head->next->next;
        head = head->next;
    }   
    cout << head->i << endl;
    
}