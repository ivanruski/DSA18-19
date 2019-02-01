#include "./math-utils.h"

using math_utils::square;
using math_utils::remainder;
using math_utils::is_even;

namespace prime_utils {
    // https://www.youtube.com/watch?v=e9IFdqSmGWM
    // link above is info that for 64-bit integers is
    // sufficient to test all the bases from [2,37]
    const int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    long long non_trivial_square_check(long long x, long long n) {
	long long xnmod = remainder(square(x), n);
	if (x != 1 && x != n - 1 && xnmod == 1)
	    return 0;

	return xnmod;
    }

    long long expmod (long long base, long long e, long long n){
	if (e == 0)
	    return 1;
	else if (is_even(e))
	    return non_trivial_square_check(expmod(base, e / 2, n), n);
	else
	    return remainder(base * expmod(base, e - 1, n), n);
    }

    bool is_prime(long long x) {
	bool prime = true;
	for (unsigned short i = 0; i < sizeof(bases); i++) {
	    if (bases[i] >= x)
		break;
	    
	    if (bases[i] < x && expmod(bases[i], x - 1, x) != 1)
		return false;
	}

	return prime;
    }

    long long next_prime(long long x) {
	if (is_even(x))
	    x += 1;

	while (is_prime(x) == false) {
	    x += 2;
	}

	return x;
    }

    long long previous_prime(long long x) {
	if (is_even(x))
	    x -= 1;

	while (is_prime(x) == false) {
	    x -= 2;
	}

	return x;
    }
}
