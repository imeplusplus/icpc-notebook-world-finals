// Finds a primitive root modulo p
// To make it works for any value of p, we must add calculation of phi(p)
// n is 1, 2, 4 or p^k or 2*p^k (p odd in both cases)

//is n primitive root of p ?
bool test(long long x, long long p) {
	long long m = p - 1;
	for(int i = 2; i * i <= m; ++i) if(!(m % i)) {
		if(fexp(x, i, p) == 1) return false;
		if(fexp(x, m / i, p) == 1) return false;
	}
	return true;
}
//find the smallest primitive root for p
int search(int p) {
	for(int i = 2; i < p; i++) if(test(i, p)) return i;
	return -1;
}
