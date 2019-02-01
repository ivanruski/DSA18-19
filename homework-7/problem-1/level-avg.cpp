#include <iostream>
#include <queue>

using namespace std;

struct node {
    int key;
    node *left, *right, *parent;
    node (int k,
	  node* l = nullptr,
	  node* r = nullptr,
	  node* p = nullptr) {
	this->key = k;
	this->left = l;
	this->right = r;
	this->parent = p;
    }
};

class bst {
private:
    

public:
    node *root;
    
    bst() {
	this->root = nullptr;
    }

    void insert(int key) {
        node *_new = new node(key);
	node *parent = nullptr;
	node *current = this->root;
	while (current != nullptr) {
	    parent = current;
	    if (_new->key < current->key)
		current = current->left;
	    else
		current = current->right;
	}

	_new->parent = parent;
	if (this->root == nullptr)
	    this->root = _new;
	else if (_new->key < parent->key)
	    parent->left = _new;
	else
	    parent->right = _new;
    }

    void print(node *root) {
	if (root == nullptr)
	    return;

	cout << root->key << " ";

	if (root->left != nullptr) {
	    cout << "L -> " << root->left->key << " ";
	}
	if (root->right != nullptr) {
	    cout << "R -> " << root->right->key;
	}
	cout << endl;
	print(root->left);
	print(root->right);
    }
	
};

int main () {
    int n;
    cin >> n;
    bst tree;

    int key;
    for (int i = 0; i < n;  i++) {
	cin >> key;
	tree.insert(key);
    }

    node *nil = new node(-1);
    queue<node*> q;
    q.push(tree.root);
    q.push(nil);
    double sum = 0;
    int level_nodes = 0;
    while (q.empty() == false) {
	node *current = q.front(); q.pop();
	if (current == nil) {
	    double avg = sum / level_nodes;
	    printf("%.2f\n", avg);

	    if (q.empty() == false) {
		q.push(nil);
		sum = 0;
		level_nodes = 0;
	    }
	    continue;
	}

	sum += current->key;
	level_nodes += 1;

	if (current->left != nullptr)
	    q.push(current->left);
	if (current->right != nullptr)
	    q.push(current->right);

    }
}

