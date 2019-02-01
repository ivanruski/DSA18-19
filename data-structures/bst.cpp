
struct node {
    int k;
    node *l, *r, *p;
    node (int key,
	  node *left = nullptr,
	  node *right = nullptr,
	  node *parent = nullptr) {
	this->k = key;
	this->l = left;
	this->r = right;
	this->p = parent;
    }
};

class bst {
private:
    node *_root;

public:
    bst() {
	_root = nullptr;
    }

    void insert (int key) {
	node *p = nullptr;
	node *c = _root;
	while (c != nullptr) {
	    p = c;
	    if (c->k > key)
		c = c->l;
	    else
		c = c->r;
	}

	node *n = new node(key);
	if (_root == nullptr)
	    _root = n;
	else if (p->k > key)
	    p->l = n;
	else
	    p->r = n;
    }
    
    void remove(int k) {
	node *n = find(_root, k);
	if (n == nullptr) return;

        if (n->l == nullptr) {
	    transplant(n, n->r);
	}
	else if (n->r == nullptr) {
	    transplant(n, n->l);
	}
	else {
	    node *succ = successor(n);
	    if (n->r != succ) {
		transplant(succ, succ->r);
		succ->r = n->r;
		succ->r->p = succ;
	    }
	    transplant(n, succ);
	    succ->l = n->l;
	    succ->l->p = succ;
	}

	delete n;
    }
     
    ~bst() {
	delete_bst(_root);
    }

private:
    node* max(node *n) {
	if (n->r != nullptr)
	    return max(n->r);
	
	return n;
    }

    node* min(node *n) {
	if (n->l != nullptr)
	    return min(n->l);

	return n;
    }

    node* successor(node *n) {
	if (n->r != nullptr)
	    return min(n->r);

	node *p = n->p;
	while (p != nullptr && p->r == n) {
	    n = p;
	    p = p->p;
	}

	return p;
    }

    node* predecessor(node *n) {
	if (n->l != nullptr)
	    return max(n->l);

	node *p = n->p;
	while (p != nullptr && p->l == n) {
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

	if (k != nullptr)
	    k->p = n->p;
    }
    
    node* find(node *n, int k) {
	if (n == nullptr)
	    return nullptr;

	if (n->k > k)
	    return find(n->l, k);
	else if (n->k < k)
	    return find(n->r, k);
	else
	    return n;
    }
    
    void delete_bst(node *n) {
	if (n == nullptr)
	    return;
	
	delete_bst(n->l);
	delete_bst(n->r);
	delete n;
    }
};
