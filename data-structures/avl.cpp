#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

struct node {
    double value;
    int h;
    node *left, *right, *p;
    node (double value,
	  node *l,
	  node *r,
	  node *p) {
	this->value = value;
	left = l;
	h = 0;
	right = r;
	this->p = p;
    }

    node (double value = 0) {
	value = value;
	p = nullptr;
	h = -1;
	left = nullptr;
	right = nullptr;
    }
    
    int height() {
	if (p == nullptr && left == nullptr && right == nullptr)
	    return -1;
	
	this->h = 1 + std::max(this->left->h, this->right->h);
	return this->h;
    }

    int balance_factor() {
	return this->right->height() - this->left->height();
    }
};

class avl {
private:
    node *nil;
    node *root;

public:
    avl() {
	nil = new node(-1);
	root = nil;
    }

    bool add (double value) {
	if (find(root, value) != nil) {
	    return false;
	}
    
	node *n = new node(value, nil, nil, nil);
	node *p = nil;
	node *c = root;
	while (c != nil) {
	    p = c;
	    if (c->value > n->value)
		c = c->left;
	    else
		c = c->right;
	}
    
	n->p = p;
	if (p == nil)
	    root = n;
	else if (p->value > n->value)
	    p->left = n;
	else
	    p->right = n;
    
	tree_fixup(n);
	return true;
    }

    bool remove(double key) {
	node *n = find(root, key);
	if (n == nil)
	    return false;

	node *p = n->p;
	if (n->left == nil)
	    transplant(n, n->right);
	else if (n->right == nil)
	    transplant(n, n->left);
	else {
	    node *succ = successor(n);
	    p = succ;
	    if (n->right != succ){
		p = succ->right;
		transplant(succ, succ->right);
		succ->right = n->right;
		n->right->p = succ;
	    }
	    transplant(n, succ);
	    succ->left = n->left;
	    n->left->p = succ;
	}
    
	delete n;
	tree_fixup(p);
	return true;
    }

    void tree_fixup(node *x) {
	if (x == nil)
	    return;
    
	int balance = x->balance_factor();

	if (std::abs(balance) < 2) {
	    return tree_fixup(x->p);
	}

    
	if (balance < 0) {
	    if (x->left->right->height() > x->left->left->height())
		left_rotate(x->left);
        
	    if (x->left->left->height() > x->left->right->height())
		right_rotate(x);
	}
	else {
	    if (x->right->left->height() > x->right->right->height())
		right_rotate(x->right);
        
	    if (x->right->right->height() > x->right->left->height())
		left_rotate(x);
	}
    
	return tree_fixup(x->p);
    }

    void print() {
	inorder_traversal(root);
	cout << std::endl;
    }

    bool contains(double value) {
	node *n = find(root,value);
	if (n == nil)
	    return false;

	return true;
    }

    ~avl() {
	delete_tree(root);
	delete nil;
    }

private:
    void inorder_traversal(node *x) {
	if (x == nil)
	    return;

	inorder_traversal(x->left);
	std::cout << x->value << " ";
	inorder_traversal(x->right);
    }
    
    void left_rotate(node *x)  {
	if (x->right == nil)
	    throw std::invalid_argument("can't perform left rotate on nil right child");

	node *y = x->right;
	x->right = y->left;
	if (y->left != nil)
	    y->left->p = x;
    
	y->p = x->p;
	if (root == x)
	    root = y;
	else if (x == x->p->left)
	    x->p->left = y;
	else
	    x->p->right = y;

	y->left = x;
	x->p = y;
	x->h = 1 + std::max(x->left->h,x->right->h);
	y->h = 1 + std::max(y->left->h,y->right->h);
    }

    void right_rotate(node *y) {
	if (y->left == nil)
	    throw std::invalid_argument("can't perform right rotate on nil left child");
    
	node *x = y->left;
	y->left = x->right;
	if (x->right != nil)
	    x->right->p = y;
    
	x->p = y->p;
	if (y == root)
	    root = x;
	else if (y == y->p->left)
	    y->p->left = x;
	else
	    y->p->right = x;

	x->right = y;
	y->p = x;
	x->h = 1 + std::max(x->left->h,x->right->h);
	y->h = 1 + std::max(y->left->h,y->right->h);
    }
    
    node* max(node *n) {
	if (n->right != nil)
	    return max(n->right);
    
	return n;
    }

    node* min(node *n) {
	if (n->left != nil)
	    return min(n->left);

	return n;
    }

    node* successor(node *n) {
	if (n->right != nil)
	    return min(n->right);

	node *p = n->p;
	while (p != nil && p->right == n) {
	    n = p;
	    p = p->p;
	}

	return p;
    }

    node* predecessor(node *n) {
	if (n->left != nil)
	    return max(n->left);

	node *p = n->p;
	while (p != nil && p->left == n) {
	    n = p;
	    p = p->p;
	}
    
	return p;
    }
    
    void transplant(node *n, node *k) {
	if (n == root)
	    root = k;
	else if (n == n->p->left)
	    n->p->left = k;
	else
	    n->p->right = k;

	if (k->p != nullptr && k->p != nil)
	    k->p = n->p;
    }
    
    node* find(node *n, double v) {
	if (n == nil)
	    return nil;

	if (n->value > v)
	    return find(n->left, v);
	else if (n->value < v)
	    return find(n->right, v);
	else
	    return n;
    }
    
    void delete_tree(node *n) {
	if (n == nil)
	    return;
    
	delete_tree(n->left);
	delete_tree(n->right);
	delete n;
    }
};
