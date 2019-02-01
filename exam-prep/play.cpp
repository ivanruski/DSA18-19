#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int fib (int n) {
    if (n == 1 || n == 0) {
	return 1;
    }

    return fib(n - 1) + fib(n - 2);
}

int main (int argc, char *args[]) {
    string str_num(args[1]); 
    stringstream str(str_num); 
    int x;  
    str >> x;
    cout << fib(x) << endl;
}
