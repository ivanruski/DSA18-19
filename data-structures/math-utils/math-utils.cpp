
namespace math_utils {
    
    long long square (long long x) {
	return x * x;
    }

    long long remainder (long long x, long long y) {
	return x % y;
    }

    bool is_even(long long x) {
	return remainder(x, 2) == 0;
    }
}
