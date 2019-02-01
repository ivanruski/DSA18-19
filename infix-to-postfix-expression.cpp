#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool isOperator (char c) {
    return c == '+' ||
	c == '-' ||
	c == '*' ||
	c == '/';
}

bool isOperand (char c) {
    return c > 96 && c < 123;
}

int precedense(char c) {
    
    switch (c) {
        case '(' : return 1;
        case ')' : return 1;
        case '+' : return 2;
        case '-' : return 2;
        case '*' : return 3;
        case '/' : return 3;
    }
}

int main() {
    vector<char> in_ex;

    while (cin) {
	char member;
	cin >> member;
	in_ex.push_back(member);
    }

    stack<char> opstack;
    vector<char> result;
    for (int i = 0; i < in_ex.size() - 1; i++) {
	char token = in_ex[i];
	
	if (isOperand(token)) {
	    result.push_back(token);
	}
	else if (token == '(') {
	    opstack.push(token);
	}
	else if (token == ')') {
	    while (opstack.top() != '(') {
		result.push_back(opstack.top());
		opstack.pop();
	    }
	    opstack.pop();
	}
	else { // must have been an operator
	    if (opstack.empty()) {
		opstack.push(token);
	    }
	    else if (precedense(token) > precedense(opstack.top())) {
		opstack.push(token);
	    }
	    else {
		while (opstack.empty() == false &&  precedense(token) <= precedense(opstack.top())) {
		    result.push_back(opstack.top());
		    opstack.pop();
		}
		opstack.push(token);
	    }
	}
    }

    while (opstack.empty() == false) {
	result.push_back(opstack.top());
	opstack.pop();
    }

    for (int i = 0; i < result.size(); i++) {
	cout << result[i] << " ";
    }
    cout << endl;
    
}
