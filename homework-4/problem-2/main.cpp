#include <iostream>
#include <unordered_set>

using namespace std;

namespace linkedlist {
    struct node {
        int data;
        node* next;
        node (int data, node* next = nullptr) {
            this->data = data;
            this->next = next;
        }
    };

    class llist {
    private:
        int size;
        void init();

    public:
        node* head;
        node* tail;

        llist();

        void push_front(int data);
        void push_last(int data);
    };

    llist::llist() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void llist::push_front(int data) {
        node* _new = new node(data);
        if (this->head == nullptr) {
            this->head = _new;
            this->tail = _new;
        }
        else {
            _new->next = this->head;
            this->head = _new;
        }

        this->size += 1;
    }

    void llist::push_last(int data) {
        node* _new = new node(data);
        this->tail->next = _new;
        this->tail = _new;
    }
}

using namespace linkedlist;

int main () {
    ios_base::sync_with_stdio(false);

    llist l;
    int n;
    cin >> n;
    int tmp;
    cin >> tmp;
    l.push_front(tmp);
    for (int i = 1; i < n; i++) {
        cin >> tmp;
        l.push_last(tmp);
    }

    unordered_set<int> visited;
    int p;
    cin >> p;
    unordered_set<int> set;
    for (int i = 0; i < p; i++) {
        cin >> tmp;
        set.insert(tmp);
    }

    node *curr = l.head;
    int match = 0;

    while (curr->next != nullptr) {
        int v1 = curr->data;
        curr = curr->next;
        int v2 = curr->data;
        if (set.find(v1) != set.end() && set.find(v2) != set.end() && 
            visited.find(v1 + v2) == visited.end()) {
            match++;
            visited.insert(v1 + v2);
        }
    }

    cout << match << endl;
}