#include <iostream>

using namespace std;
struct node {
    size_t size;
    int head;
    node* cloned_from;
};

void set_default(node* store[]) {
    store[0] = new node();
    store[0]->size = 0;
    store[0]->head = 0;
    store[0]->cloned_from = nullptr;
}

int main(int argc, char const *argv[])
{
    int n; cin >> n;
    node* store[n + 1];
    set_default(store);   

    unsigned long long sum = 0;
    int p, m;
    for (int i = 1; i <= n; i++) {
        cin >> p >> m;
        if (m == 0) {
            store[i] = new node();
            store[i]->cloned_from = store[p]->cloned_from->cloned_from;
            store[i]->size = store[p]->cloned_from->size;
            store[i]->head = store[p]->cloned_from->head;
        } else {
            store[i] = new node();
            store[i]->cloned_from = store[p];
            store[i]->size = store[p]->size + m;
            store[i]->head = m;
        }

        sum += store[i]->size;
    } 
    cout << sum << endl;
    return 0;
}