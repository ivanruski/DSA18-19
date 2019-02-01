#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

struct node {
    char c;
    node *left, *right, *p;
    node (char value,
	  node *l = nullptr,
	  node *r = nullptr,
	  node *pr = nullptr) {
	c = value;
	left = l;
	right = r;
	p = pr;
    }
};

node *to_exp_tree(string expression) {
    stack<node*> s;
    for (int i = expression.length() - 1; i > -1; i--) {
	if (expression[i] != '-' && expression[i] != '+') {
	    node *n = new node(expression[i]);
	    s.push(n);
	}
	else {
	    node *sign = new node(expression[i]);
	    node *op1 = s.top(); s.pop();
	    node *op2 = s.top(); s.pop();
	    op1->p = sign;
	    op2->p = sign;
	    sign->left = op1;
	    sign->right = op2;
	    s.push(sign);
	}
    }
    node *result = s.top(); s.pop();
    return result;
}

void inorder(node *root,
	     int &pos,
	     int &neg,
	     vector<char> &exp,
	     int sign) {
    if (root == nullptr)
	return;

    inorder(root->left, pos, neg, exp, sign);

    if (root->c == '+' && sign == 0 ||
	root->c == '-' && sign == 1) {
	pos += 1;
	exp.push_back('+');
    }
    else if(root->c == '-' && sign == 0 ||
	    root->c == '+' && sign == 1) {
	neg += 1;
	exp.push_back('-');
    }
    else {
	exp.push_back(root->c);
    }

    int next_sign = 0;
    if (root->c == '-' && sign == 0 ||
	root->c == '+' && sign == 1) {
	next_sign = 1;
    }
    
    inorder(root->right, pos, neg, exp, next_sign);
}

void print_ones(int size) {
    for (int i = 0; i < size; i++) {
	cout << 1 << endl;
    }
}

int main () {
    string expr;
    cin >> expr;
    node *root = to_exp_tree(expr);
    int pos = 1, neg = 0;
    vector<char> exp;
    exp.push_back('+');
    inorder(root, pos, neg, exp, 0);

    for (int i = 0; i < exp.size(); i++) {
	//	cout << exp[i] << " ";
    }
    //cout << endl;

    if (pos > neg) {
	int psum = pos;
	int neg_left = neg;
    
	for (int i = 1; i < exp.size(); i++) {
	    if (exp[i] == '?' && exp[i - 1] == '+') {
		cout << 1 << endl;
	    }
	    else if (exp[i] == '?' && exp[i - 1] == '-') {
		int d = psum / neg_left;
		psum = psum - d;
		neg_left -= 1;
		cout << d << endl;
	    }
	}
    }
    else if (pos < neg) {
	int nsum = neg;
	int p_left = pos;

	for (int i = 1; i < exp.size(); i++) {
	    if (exp[i] == '?' && exp[i - 1] == '-') {
		cout << 1 << endl;
	    }
	    else if (exp[i] == '?' && exp[i - 1] == '+') {
		int d = nsum / p_left;
		nsum = nsum - d;
		p_left -= 1;
		cout << d << endl;
	    }
	}
    }
    else {
	print_ones(pos + neg);
    }
}
