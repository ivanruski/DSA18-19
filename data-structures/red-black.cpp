#include <stdexcept>

enum color { red, black };

struct node {
    color c;
    int k;
    node *l, *r, *p;
    node (int key,
	  color color = red,
	  node *left = nullptr,
	  node *right = nullptr,
	  node *parent = nullptr) {
	this->k = key;
	this->c = color;
	this->l = left;
	this->r = right;
	this->p = parent;
    }
};

class rb_tree {
private:
    node *_root;
    node *nil;

public:
    rb_tree() {
	nil = new node(0, black);
	_root = nil;
    }

    void insert (int key) {
	node *p = nil;
	node *c = _root;
	while (c != nil) {
	    p = c;
	    if (c->k > key)
		c = c->l;
	    else
		c = c->r;
	}

	node *n = new node(key,red,nil,nil, p);
	if (_root == nil)
	    _root = n;
	else if (p->k > key)
	    p->l = n;
	else
	    p->r = n;

	return insert_fixup(n);
    }

    void insert_fixup(node *z) {
	while (z->p->c == red) {
	    if (z->p == z->p->p->l) {
		node *y = z->p->p->r;
		if (y->c == red) {
		    y->c = black;
		    z->p->c = black;
		    z->p->p->c = red;
		    z = z->p->p;
		}
		else {
		    if (z == z->p->r) {
			z = z->p;
			left_rotate(z);
		    }
		    z->p->c = black;
		    z->p->p->c = red;
		    right_rotate(z->p);
		}
	    }
	    else {
		node *y = z->p->p->l;
		if (y->c == red) {
		    y->c = black;
		    z->p->c = black;
		    z->p->p->c = red;
		    z = z->p->p;
		}
		else {
		    if (z == z->p->r) {
			z = z->p;
			right_rotate(z);
		    }
		    z->p->c = black;
		    z->p->p->c = red;
		    left_rotate(z->p);
		}
	    }
	    
	}
	_root->c = black;
    }
    
    void remove(int k) {
	node *z = find(_root, k);
	if (z == nil) return;

        if (z->l == nil) {
	    transplant(z, z->r);
	}
	else if (z->r == nil) {
	    transplant(z, z->l);
	}
	else {
	    node *succ = successor(z);
	    if (z->r != succ) {
		transplanth
		    (succ, succ->r);
		succ->r = z->r;
		z->r->p = succ;
	    }
	    transplant(z, succ);
	    succ->l = z->l;
	    z->l->p = succ;
	}

	delete z;
    }
     
    ~rb_tree() {
	delete_tree(_root);
	delete nil;
    }

private:
    void left_rotate(node *x)  {
	if (x->r == nil)
	    throw std::invalid_argument("can't perform left rotate on nil right child");

	node *y = x->r;
	x->r = y->l;
	if (y->l != nil)
	    y->l->p = x;

	y->p = x->p;
	if (_root == x)
	    _root = y;
	else if (x == x->p->l)
	    x->p->l = y;
	else
	    x->p->r = y;

	y->l = x;
	x->p = y; 
    }

    void right_rotate(node *y) {
	if (y->l == nil)
	    throw std::invalid_argument("can't perform right rotate on nil left child");
	
	node *x = y->l;
	y->l = x->r;
	if (x->r != nil)
	    x->r->p = y;
	
	x->p = y->p;
	if (y == _root)
	    _root = x;
	else if (y == y->p->l)
	    y->p->l = x;
	else
	    y->p->r = x;

	x->r = y;
	y->p = x;
    }
    
    node* max(node *n) {
	if (n->r != nil)
	    return max(n->r);
	
	return n;
    }

    node* min(node *n) {
	if (n->l != nil)
	    return min(n->l);

	return n;
    }

    node* successor(node *n) {
	if (n->r != nil)
	    return min(n->r);

	node *p = n->p;
	while (p != nil && p->r == n) {
	    n = p;
	    p = p->p;
	}

	return p;
    }

    node* predecessor(node *n) {
	if (n->l != nil)
	    return max(n->l);

	node *p = n->p;
	while (p != nil && p->l == n) {
	    n = p;
	    p = p->p;
	}

	return p;
    }
    
    void transplant(node *n, node *k) {
	if (n == _root)
	    _root = k;
	else if (n == n->p->l)
	    n->p->l = k;
	else
	    n->p->r = k;

	k->p = n->p;
    }
    
    node* find(node *n, int k) {
	if (n == nil)
	    return nil;

	if (n->k > k)
	    return find(n->l, k);
	else if (n->k < k)
	    return find(n->r, k);
	else
	    return n;
    }
    
    void delete_tree(node *n) {
	if (n == nil)
	    return;
	
	delete_tree(n->l);
	delete_tree(n->r);
	delete n;
    }
};

int main() {
}
