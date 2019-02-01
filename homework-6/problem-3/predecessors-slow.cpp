#include <iostream>
#include <queue>

using namespace std;

struct node {
    int key;
    node *left, *right, *parent;
    vector<int> ancestors;

    node(int k) {
	this->key = k;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
    }
};

class binary_tree {
private:
    node *root;
    node *nil;

public:
    binary_tree() {
	this->root = nullptr;
	this->nil = new node(-1);
    }
    
    void insert(int parent_key, int child_key) {
	if (this->root == nullptr) {
	    this->add_root(parent_key, child_key);
	    return;
	}
	
	node* parent = this->find(parent_key, a);
	node* child = new node(child_key);
	if (parent->left == nullptr)
	    parent->left = child;
	else
	    parent->right = child;
	
	child->parent = parent;
    }

    void print() {
	queue<node*> q;
	q.push(this->root);

	while (q.empty() == false) {
	    node* curr = q.front(); q.pop();
	    cout << "Node -> " << curr->key << " ";
	    cout << "left -> ";
	    if (curr->left != nullptr) {
		cout << curr->left->key << " ";
		q.push(curr->left);
	    }
	    else {
		cout << " null ";
	    }

	    cout << "right -> ";
	    if (curr->right != nullptr) {
		cout << curr->right->key << " ";
		q.push(curr->right);
	    }
	    else {
		cout << " null ";
	    }
	    
	    cout << endl;
	}
    }

    void predecessor(int key, int i) {
	int depth = 0;
	node* node = this->find(key, depth);
	return this->get_parent(node, i);
    }

    void get_parent(node* n, int i) {
	if (i == 0) {
	    cout << n->key << "\n";
	    return;
	}
	
	this->get_parent(n->parent, i - 1);
    }

private:
    int node_depth(node *n) {
	int depth = 0;
	while (n != this->root) {
	    n = n->parent;
	    depth += 1;
	}
	
	return depth;
    }
    
    void add_root(int key, int child_key) {
	this->root = new node(key);
	node* child = new node(child_key);
        this->root->left = child;
	child->parent = this->root;
	child->ancestors.insert(child->ancestors.begin(), key);
    }
    
    node* find(int key, int &depth) {
	queue<node*> q;
	q.push(this->root);
	q.push(this->nil);
	
	while (q.empty() == false) {
	    node* curr = q.front(); q.pop();
	    if (curr == this->nil) {
		depth += 1;
		q.push(this->nil);
	    }
	    
	    if (curr->key == key)
		return curr;

	    if (curr->left != nullptr)
		q.push(curr->left);
	    if (curr->right != nullptr)
		q.push(curr->right);
	}

	throw invalid_argument("key not found");
    }
    
};

int main() {
    vector<int> v;
    for (int i = 0; i < 20; i++) {
	v.insert(v.begin(), i);
    }

    for (int i = 0; i < 20; i++) {
	cout << v[i] << " ";
    }
    cout << endl;
    return 0;


    binary_tree bt;
    int n, k, j;
    cin >> n;
    for (int i = 1; i < n; i++) {
	cin >> k >> j;
	bt.insert(k, j);
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
	cin >> k >> j;
	bt.predecessor(k, j);
    }
}
