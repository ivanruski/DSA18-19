#include <vector> 
#include <iostream>
#include <math.h>
#include <inttypes.h>

using namespace std;

uint64_t sum_one_to_n(uint64_t n) {
    if (n == 0) return 0;
    
    u_int64_t sum = 0;

    if (n % 2 == 0) {
        sum = ( n / 2 ) * (n + 1);
    }
    else {
        sum = n * ( (n + 1) / 2 );
    }

    return sum;
}

int avg_one_to_n(uint64_t n) {
    if (n == 0)
        return 0;

    return sum_one_to_n(n) / n;
}

int count_steps(uint64_t n) {
    int steps = 0;
    int avg = avg_one_to_n(n);

    while (avg != 0) {
        n -= avg;
        steps++;
        avg = avg_one_to_n(n);
    }

    return steps;
}

int main () {
    int t;
    cin >> t;

    int n;
    while (t > 0) {
        cin >> n;
        cout << count_steps(n) << endl;
        t--;
    }
}