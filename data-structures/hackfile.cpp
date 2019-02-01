/* 
 * Simple hashset for integers using std::hash for hashing
 *
 * The idea is to write sceleton of primitive hashset
 * Without writing my own hash function
 *
 * The data strucutre is needed for homework 9
 */

#include <functional>
#include <iostream>

namespace math_utils {
    
    long long square (long long x) {
	return x * x;
    }

    long long remainder (long long x, long long y) {
	return x % y;
    }

    bool is_even(long long x) {
	return remainder(x, 2) == 0;
    }
}


using math_utils::square;
using math_utils::remainder;
using math_utils::is_even;

namespace prime_utils {
    // https://www.youtube.com/watch?v=e9IFdqSmGWM
    // link above is info that for 64-bit integers is
    // sufficient to test all the bases from [2,37]
    const int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    long long non_trivial_square_check(long long x, long long n) {
	long long xnmod = remainder(square(x), n);
	if (x != 1 && x != n - 1 && xnmod == 1)
	    return 0;

	return xnmod;
    }

    long long expmod (long long base, long long e, long long n){
	if (e == 0)
	    return 1;
	else if (is_even(e))
	    return non_trivial_square_check(expmod(base, e / 2, n), n);
	else
	    return remainder(base * expmod(base, e - 1, n), n);
    }

    bool is_prime(long long x) {
	bool prime = true;
	for (unsigned short i = 0; i < sizeof(bases); i++) {
	    if (bases[i] >= x)
		break;
        
	    if (bases[i] < x && expmod(bases[i], x - 1, x) != 1)
		return false;
	}

	return prime;
    }

    long long next_prime(long long x) {
	if (is_even(x))
	    x += 1;

	while (is_prime(x) == false) {
	    x += 2;
	}

	return x;
    }

    long long previous_prime(long long x) {
	if (is_even(x))
	    x -= 1;

	while (is_prime(x) == false) {
	    x -= 2;
	}

	return x;
    }
}


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


typedef long long int64;

class int64_dict {
private:
    short load_factor = 2;
    int size;
    int max_size;
    llist<int64> *buckets;
    int a,b,p;
public:
    int64_dict(int s);
    ~int64_dict();

    bool insert(int64 data);
    bool exist(int64 data);
    int get_size();
    
private:
    int h(int64 data);
    bool load_factor_limit_reached();
    void resize();
};

int64_dict::int64_dict(int s = 16) {
    size = 0;
    max_size = s;
    buckets = new llist<int64>[max_size];
    a = 31;
    b = prime_utils::previous_prime(s);
    p = prime_utils::next_prime(s);
    
}

int64_dict::~int64_dict() {
    //TODO:
}

bool int64_dict::insert(int64 data) {
    if (load_factor_limit_reached()) {
	resize();
    }
    
    int index = h(data);
    if (buckets[index].exist(data))
	return false;

    buckets[index].push_last(data);
    size++;
    return true;
}

bool int64_dict::exist(int64 data) {
    int index = h(data);
    return buckets[index].exist(data);
}

int int64_dict::get_size() {
    return size;
}

int int64_dict::h(int64 data) {
    int result =
	math_utils::remainder(
			      math_utils::remainder(((a * data) + b),p),
			      max_size);

    if (result < 0)
	return -result;

    return result;
}

bool int64_dict::load_factor_limit_reached() {
    return false;
    //    return max_size / size <= 2;
}

void int64_dict::resize() {
    // llist<int64> *enlarged = new llist<int64>[max_size * 2];
    
    // for (int i = 0; i < max_size; i++) {
    //     if (buckets[i].empty())
    //         continue;

    //     llist<int64>::node *head = buckets[i].get_head();
    //     while (head != nullptr) {
    //         int index = 
    //     }
    // }
}



int main () {
    int n;
    std::cin >> n;
    int64_dict d(n * 2 + 1);

    int64 num;
    for (int i = 0; i < n; i++) {
	std::cin >> num;
	d.insert(num);
    }

    std::cout << d.get_size() << std::endl;
}
