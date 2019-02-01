#include <iostream>

template <class T>
class llist {
public:
    struct node {
        T data;
        node* next;
        node (T data, node* next = nullptr) {
            this->data = data;
            this->next = next;
        }
    };

private:
    int size;
    node* head;
    node* tail;
    void init();

public:
    llist();
    ~llist();

    void print();
    void push_front(T data);
    void push_last(T data);
    void remove(T data);

    bool exist(T data);
    bool empty();

    //    node* get_head();
};


template <class T>
llist<T>::llist() {
    this->init();
}

/* template <class T> */
/* llist<T>::node* llist<T>::get_head() { */
/*     return this->head; */
/* } */

template <class T>
void llist<T>::print() {
    node* curr = this->head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

template <class T>
void llist<T>::push_front(T data) {
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

template <class T>
void llist<T>::push_last(T data) {
    node* _new = new node(data);
    if (this->head == nullptr) {
        this->head = _new;
        this->tail = _new;
    }
    else {
        this->tail->next = _new;
        this->tail = _new;
    }

    this->size += 1;
}

template <class T>
bool llist<T>::empty() {
    return this->size == 0;
}

template <class T>
void llist<T>::remove(T data) {
    node *prev = nullptr;
    node *curr = this->head;
    while (curr != nullptr && curr->data != data) {
	prev = curr;
	curr = curr->next;
    }

    if (curr == nullptr)
	return;

    if (curr == this->head)
	this->head = curr->next;
    else if (curr == this->tail)
	this->tail = prev;
    else
	prev->next = curr->next;

    this->size -= 1;
    delete curr;
}

template <class T>
bool llist<T>::exist(T data) {
    node *curr = this->head;
    while (curr != nullptr && curr->data != data) {
	curr = curr->next;
    }

    return curr != nullptr && curr->data == data;
}

template <class T>
llist<T>::~llist() {
    node* tmp = nullptr;
    while (this->head != nullptr) {
        tmp = this->head;
        this->head = this->head->next;
        delete tmp;
    }
}

//private
template <class T>
void llist<T>::init() {
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}
