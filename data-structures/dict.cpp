/* 
 * Simple hashset for integers using std::hash for hashing
 *
 * The idea is to write sceleton of primitive hashset
 * Without writing my own hash function
 *
 * The data strucutre is needed for homework 9
 */

#include <functional>
#include "./llist/llist.h"
#include "./math-utils/prime-utils.h"

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
    // ((a * data + b) mod p) mod n;
    return
	math_utils::remainder(
			      math_utils::remainder(((a * data) + b),p),
			      max_size);
}

bool int64_dict::load_factor_limit_reached() {
    return false;
    //    return max_size / size <= 2;
}

void int64_dict::resize() {
    // llist<int64> *enlarged = new llist<int64>[max_size * 2];
    
    // for (int i = 0; i < max_size; i++) {
    // 	if (buckets[i].empty())
    // 	    continue;

    // 	llist<int64>::node *head = buckets[i].get_head();
    // 	while (head != nullptr) {
    // 	    int index = 
    // 	}
    // }
}



int main () {
    int n;
    std::cin >> n;
    int64_dict d(n * 2 + 1);

    int64 num;
    for (int i = 0; i < 100; i++) {
	std::cin >> num;
	d.insert(num);
    }

    std::cout << d.get_size() << std::endl;
}
