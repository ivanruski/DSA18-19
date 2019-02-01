#include <iostream>
#include <cmath>

using namespace std;

class max_heap {
private:
    int size;
    int heap_size;
    int *heap;


public:
    max_heap(int size = 16) {
	this->size = size;
	this->heap_size = 0;
	this->heap = new int[size];
    }

    int top() {
	return this->heap[0];
    }

    int get_size() {
	return heap_size;
    }
    
    void add (int key) {
	if (this->heap_size == size) {
	    this->reallocate();
	}
	this->heap[this->heap_size] = key;

	int i = this->heap_size;
	int pi = this->parent(i);
	while (pi >= 0 && this->heap[pi] < key) {
	    int tmp = this->heap[pi];
	    this->heap[pi] = key;
	    this->heap[i] = tmp;
	    i = pi;
	    pi = this->parent(pi);
	}
	
        this->heap_size += 1;
    }

    void remove_top () {
	this->heap_size -= 1;
	int leaf = this->heap[heap_size];
	this->heap[heap_size] = this->heap[0];
	this->heap[0] = leaf;

	return this->heapify(0);
    }

    void print() {
	for (int i = 0; i < this->heap_size; i++) {
	    cout << this->heap[i] << " ";
	}
	cout << endl;
    }

    ~max_heap() {
	delete this->heap;
    }

private:
    int parent(int index) {
	return (index - 1) / 2;
    }

    int left(int index) {
	return 2 * index + 1;
    }

    int right (int index) {
	return 2 * index + 2;
    }

    void heapify(int i) {
	int greatest = i;
	if (left(i) < heap_size && heap[left(i)] > heap[greatest]) {
	    greatest = left(i);
	}
	if (right(i) < heap_size && heap[right(i)] > heap[greatest]) {
	    greatest = right(i);
	}

	if (greatest != i) {
	    int tmp = heap[i];
	    heap[i] = heap[greatest];
	    heap[greatest] = tmp;
	    return heapify(greatest);
	}
    }
    
    void reallocate() {
	int new_size = this->size * 2;
	int *new_heap = new int[new_size];
	for (int i = 0; i < this->size; i++) {
	    new_heap[i] = this->heap[i]; 
	}
	int *old_heap = this->heap;
	this->heap = new_heap;
	delete old_heap;
	this->size = new_size;
    }
};

class min_heap {
private:
    int size;
    int heap_size;
    int *heap;

public:
    min_heap(int n = 16) {
	size = n;
	heap_size = 0;
	heap = new int[n];
    }

    int top() {
	return heap[0];
    }

    int get_size() {
	return heap_size;
    }
    
    void add(int key) {
	if (heap_size == size) {
	    reallocate();
	}

	heap[heap_size] = key;
	int i = heap_size;
	while (parent(i) >= 0 && heap[parent(i)] > heap[i]) {
	    int tmp = heap[parent(i)];
	    heap[parent(i)] = heap[i];
	    heap[i] = tmp;
	    i = parent(i);
	}

	heap_size += 1;
    }

    void remove_top() {
	heap_size -= 1;
	int leaf = heap[heap_size];
	heap[heap_size] = heap[0];
	heap[0] = leaf;

	heapify(0);
    }

    void print() {
	for (int i = 0; i < this->heap_size; i++) {
	    cout << this->heap[i] << " ";
	}
	cout << endl;
    }

    ~min_heap() {
	delete this->heap;
    }

   private:
    int parent(int index) {
	return (index - 1) / 2;
    }

    int left(int index) {
	return 2 * index + 1;
    }

    int right (int index) {
	return 2 * index + 2;
    }

    void heapify(int i) {
        int smallest = i;

	if (left(i) < heap_size && heap[left(i)] < heap[i]) {
	    smallest = left(i);
	}
	if (right(i) < heap_size && heap[right(i)] < heap[smallest]) {
	    smallest = right(i);
	}

	if (smallest != i) {
	    int tmp = heap[i];
	    heap[i] = heap[smallest];
	    heap[smallest] = tmp;
	    return heapify(smallest);
	}
    }
    
    void reallocate() {
	int new_size = this->size * 2;
	int *new_heap = new int[new_size];
	for (int i = 0; i < this->size; i++) {
	    new_heap[i] = this->heap[i]; 
	}
	int *old_heap = this->heap;
	this->heap = new_heap;
	delete old_heap;
	this->size = new_size;
    }
};

void print_median(max_heap &lesser, min_heap &higher) {
    if (lesser.get_size() == higher.get_size()) {
	double avg = ((double)lesser.top() + (double)higher.top()) / 2;
	printf("%.1f\n",avg);
    }
    else if (lesser.get_size() > higher.get_size()) {
	printf("%.1f\n", (double)lesser.top());
    }
    else {
	printf("%.1f\n", (double)higher.top());
    }
}

void add_x(max_heap &lesser, min_heap &higher, int x) {
    if (lesser.get_size() == 0 || x < lesser.top()) {
	lesser.add(x);
    }
    else {
	higher.add(x);
    }
}

void rebalance(max_heap &lesser, min_heap &higher) {
    if (abs(lesser.get_size() - higher.get_size()) <= 1) {
	return;
    }

    if (lesser.get_size() > higher.get_size()) {
	int m = lesser.top(); lesser.remove_top();
	higher.add(m);
    }
    else {
	int m = higher.top(); higher.remove_top();
	lesser.add(m);
    }
}

int main () {
    int n;
    cin >> n;

    max_heap lesser((n / 2) + 1);
    min_heap higher((n / 2) + 1);
    int x;
    for (int i = 0; i < n; i++) {
	cin >> x;
        add_x(lesser,higher, x);
	rebalance(lesser, higher);
        print_median(lesser, higher);
    }

    /*
cout << "max->top = " << max.top() << "  "
	     << "max->size = " << max.get_size() << "  "
	     << "min->top = " << min.top() << "  "
	     << "min->size = " << min.get_size() << endl;
     */
    
}
