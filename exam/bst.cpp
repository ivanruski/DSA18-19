#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

struct node {
    node *l;
    node *r;
    node *p;
    int key;
    
    node (int k) {
        this->key = k;
        this->l = nullptr;
        this->r = nullptr;
    }
};

class bst {
public:
    node *root;
    
    bst () {
        root = nullptr;
    }
    
    void add(int k) {
        if (root == nullptr) {
            root = new node(k);
        }   
        else {
            add_node(root, k);
        }
    }
    
    void add_node (node *n, int k) {
        if (n->key == k) {
            return;
        }
        
        if (n->key < k) {
            if (n->r == nullptr) {
                n->r = new node(k);
                n->r->p = n;
            }
            else 
		{
		    add_node(n->r, k);
		}
        }
        else {
	    if (n->l == nullptr) {
		n->l = new node(k);
		n->l->p = n;
	    }   
            else {
                add_node(n->l, k);
            }
        }
    }
    
    void remove(int k) {
	//cout << "remove " << k << " root " << root->key << endl;
        node *n = find_node(root, k);
        if (n == nullptr) {
            return;
        }
        
        if (n->l == nullptr) {
            transplant(n, n->r);
        }
        else if (n->r == nullptr) {
            transplant(n, n->l);
        }
        else {
            node *y = min(n->r);
            if (y->p != n) {
                transplant(y, y->r);
                y->r = n->r;
		n->r->p = y;
            }
            transplant(n, y);
            y->l = n->l;
            n->l->p = y;
        }
        
        delete n;
    }

    void transplant(node *n, node *m) {
        if (n == root) {
            root = m;
        }
        else if (n->p->l == n) {
            n->p->l = m;
        }
        else {
            n->p->r = m;
        }
        
        if (m != nullptr) {
            m->p = n->p;
        }
    }
    
    node *successor(node *n) {
	if (n->r != nullptr) {
	    return min(n->r);
	}
        
	node *p = n->p;
	while (p != nullptr && p->r == n) {
	    n = p;
	    p = p->p;
	}
	return p;
    }
    
    node *min (node *n) {
        while (n->l != nullptr) {
            n = n->l;
        }
        
        return n;
    }
    
    node* find_node(node *n, int k) {
        if (n == nullptr) {
            return nullptr;
        }
        
        if (n->key == k) {
            return n;
        }
        if (n->key > k) {
            return find_node(n->l, k);
        }
        else {
            return find_node(n->r, k);
        }
    }
    
    void odd () {
        node *nil = new node(-1);
        node *curr = root;
        queue<node*> q;
        q.push(curr);
        q.push(nil);
        
        int level = 1;
        while (q.empty() == false) {
            node *t = q.front(); q.pop();
            
            if (t == nil) {
                level +=1 ;
                
                if (q.empty() == true) {
                    break;
                }
                q.push(nil);
                continue;
            }
            
            if (level % 2 != 0) {
                cout << t->key << " ";
            }
            
            if (t->l != nullptr) {
                q.push(t->l);
            }
            if (t->r != nullptr) {
                q.push(t->r);
            }
        }
    }
    
    void print () {
        print_node(this->root);
    }
    
    void print_node (node *n) {
        cout << n -> key << " ";
        
        if (n->l != nullptr) {
            print_node(n->l);
        }
        if (n->r != nullptr) {
            print_node(n->r);
        }
    } 
};

int main() {
    int n;
    cin >> n;
    bst tree;
    for (int i = 0; i < n; i++) {
        string op;
        cin >> op;
        if (op == "add") {
            int k;
            cin >> k;
            tree.add(k);
        }
        if (op == "remove") {
            int k;
            cin >> k;
            tree.remove(k);
        }
        if (op == "print") {
            tree.print();
        }
        if (op == "print_odd_layers") {
            tree.odd();
        }
    }
}
