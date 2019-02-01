#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int val) {
	this->value = val;
	this->next = nullptr;
    }

    Node(int val, Node* n) {
	this->value = val;
	this->next = n;
    }
};

class LinkedList {
private:
    int size;
    Node* head;
    
public:
    void add(int val, int pos) {
        if (pos < 0 || pos > this->size) {
	    this->add_to_end(val);
	}
	else {
	    this->insert_at(val, pos);
	}
    }
    
    void print() {
	Node* curr = this->head;
	while (curr != nullptr) {
	    cout << curr->value << "#";
	    curr = curr->next;
	}
    }

    void remove(int pos) {
        if (pos < 0 || pos >= this->size) {
	    cout << "remove_failed";
	    return;
	}

	if (pos == 0) {
	    remove_head();
	    return;
	}

	int index = 0;
	Node *curr = this->head;
	while (index + 1 < pos && curr != nullptr) {
	    index++;
	    curr = curr->next;
	}
	Node *n = curr->next;
	curr->next = n->next;
	delete n;
	this->size -= 1;
    }

    void reverse() {
	if (this->size < 2)
	    return;

	Node *new_begining = this->reverse_from(this->head);
        this->head = new_begining;
    }

    void remove_all(int val) {
	if (this->size == 0) return;
	
	Node* prev = this->head;
	Node* curr = this->head->next;
	while (curr != nullptr) {
	    if (curr->value == val) {
		prev->next = curr->next;
		delete curr;
		curr = prev->next;
		this->size -= 1;
	    }
	    else {
		prev = curr;
		curr = curr->next;
	    }
	}

	if (this->head->value == val) {
	    this->remove_head();
	}
    }

    void group(int a, int b) {
        if (a < 0 || a >= this->size ||
	    b < 0 || b >= this->size ||
	    a > b) {
	    cout << "fail_grouping";
	    return;
	}

	Node* before_a = nullptr;
	Node* from;
	if (a == 0) {
	    from = this->head;
	}
	else {
	    before_a = this->get_element_before_index(a);
	    from = before_a->next;
	}

	int sum = 0;
	Node* prev;
	for (int i = a; i < b; i++) {
	    sum += from->value;
	    prev = from;
	    from = from->next;
	    delete prev;
	}
	sum += from->value;
	Node* _new = new Node(sum, from->next);
	delete from;
	
	if (a == 0)
	    this->head = _new;
	else
	    before_a->next = _new;
    }

    void count(int val) {
        int encnt = 0;
	Node *curr = this->head;
	while (curr != nullptr) {
	    if (curr->value == val)
		encnt += 1;

	    curr = curr->next;
	}
	cout << encnt;
    }

    void is_palindrome() {
	if (this->size < 2) {
	    cout << "true";
	    return;
	}

	int mid_index;
	if (this->size % 2 == 0) {
	    mid_index = this->size/2;
	}
	else {
	    mid_index = (this->size/2) + 1; 
	}

	Node *m = this->get_element_before_index(mid_index);
	Node *middle = this->reverse_from(m->next);
	Node *start = this->head;
	Node *mstart = middle;
        
	bool palindrome = true;
	for (int i = 0; i < this->size / 2; i++) {
	    if (mstart->value != start->value) {
		palindrome = false;
		break;
	    }
	    mstart = mstart->next;
	    start = start->next;
	}

	Node* n = this->reverse_from(middle);
	m->next = n;
	
	if (palindrome)
	    cout << "true";
	else
	    cout << "false";
    }

    LinkedList() {
	this->size = 0;
	this->head = nullptr;
    } 

    ~LinkedList() {
	if (head == nullptr)
	    return;
	
	Node *curr = head;
	Node *next = curr->next;
	
	while (next != nullptr){
           delete curr;
	   curr = next;
	   next = curr->next;
	}
	delete curr;
	this->size = 0;
    }

  
private:
    Node* get_element_at_index(int atindex) {
      	int index = 0;
	Node *c = this->head;
	while (index < atindex) {
	    c = c->next;
	    index++;
	}
        return c;
    }
    
    Node* get_element_before_index(int atindex) {
	if (atindex == 0) {
	    return nullptr;
	}
	
	int index = 0;
	Node *c = this->head;
	while (index < atindex - 1) {
	    c = c->next;
	    index++;
	}
        return c;
    }
    
    Node* reverse_from(Node *start) {
        Node *prev = nullptr;
	Node *curr = start;
	Node *next = start->next;

	while (next != nullptr) {
	    curr->next = prev;
	    prev = curr;
	    curr = next;
	    next = next->next;
	}
	
	curr->next = prev;
	return curr;
    }
    
    void insert_at(int val, int pos) {
	int index = 0;
	Node* curr = this->head;
	while (index + 1 < pos && curr != nullptr) {
	    index++;
	    curr = curr->next;
	}

	Node* _new = new Node(val);
	if (this->size == 0) {
	    this->head = _new;
	}
	else if(pos == 0) {
	    _new->next = this->head;
	    this->head = _new;
	}
	else {
	    _new->next = curr->next;
	    curr->next = _new;
	}

	this->size += 1;
    }

    void add_to_end(int val) {
	if (this->size == 0) {
	    this->head = new Node(val);
	}
	else { 
	    Node* curr = this->head;
	    while (curr->next != nullptr) {
		curr = curr->next;
	    }

	    curr->next = new Node(val);
	}
	this->size += 1;
	cout << "add_last";
    }

    void remove_head() {
	if (this->size == 0)
	    return;
	
	Node* n = this->head;
	this->head = n->next;
	delete n;
	this->size -= 1;
    }
};

int main() {
    int cases;
    std::cin >> cases;
    for (int i = 0; i < cases; i++) {
        LinkedList ll;
        int ops;
        std::string op;
        std::cin >> ops;
        for (int j = 0; j < ops; j++) {
            std::cin >> op;

            if (op == "count") {
                int arg1;
                std::cin >> arg1;
                ll.count(arg1);
            }

            if (op == "add") {
                int arg1, arg2;
                std::cin >> arg1 >> arg2;
                ll.add(arg1, arg2);
            }

            if (op == "print") {
                ll.print();
            }

            if (op == "remove") {
                int arg1;
                std::cin >> arg1;
                ll.remove(arg1);
            }

            if (op == "reverse") {
                ll.reverse();
            }

            if (op == "remove_all") {
                int arg1;
                std::cin >> arg1;
                ll.remove_all(arg1);
            }

            if (op == "group") {
                int arg1, arg2;
                std::cin >> arg1 >> arg2;
                ll.group(arg1, arg2);
            }

            if (op == "is_palindrom") {
                ll.is_palindrome();
            }
        }

        std::cout << std::endl;

    }
    return 0;
}
