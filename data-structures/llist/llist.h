#include <iostream>

template <class T>
class llist {
private:
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

    
};

//public

template <class T>
llist<T>::llist() {
    this->init();
}

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