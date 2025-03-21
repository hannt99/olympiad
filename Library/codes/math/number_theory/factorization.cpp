lint mul(lint x, lint y, lint mod) { return (__int128)x * y % mod; }

lint ipow(lint x, lint y, lint p) {
	lint ret = 1, piv = x % p;
	while (y) {
		if (y & 1)
			ret = mul(ret, piv, p);
		piv = mul(piv, piv, p);
		y >>= 1;
	}
	return ret;
}

namespace factors {
bool miller_rabin(lint x, lint a) {
	if (x % a == 0)
		return 1;
	lint d = x - 1;
	while (1) {
		lint tmp = ipow(a, d, x);
		if (d & 1)
			return (tmp != 1 && tmp != x - 1);
		else if (tmp == x - 1)
			return 0;
		d >>= 1;
	}
}
// 100000 primes in 3sec
bool isprime(lint n) {
	if (n < 2 || (n % 2 == 0))
		return (n == 2);
	vector<lint> seeds;
	if (n < (1 << 30))
		seeds = {2, 7, 61};
	else
		seeds = {2, 325, 9375, 28178, 450775, 9780504};
	for (auto &i : seeds) {
		if (n == i)
			return 1;
		if (miller_rabin(n, i))
			return 0;
	}
	return 1;
}
lint f(lint x, lint n, lint c) { return (c + mul(x, x, n)) % n; }
void rec(lint n, vector<lint> &v) {
	if (n == 1)
		return;
	if (n % 2 == 0) {
		v.push_back(2);
		rec(n / 2, v);
		return;
	}
	if (isprime(n)) {
		v.push_back(n);
		return;
	}
	lint a, b, c;
	while (1) {
		a = rand() % (n - 2) + 2;
		b = a;
		c = rand() % 20 + 1;
		do {
			a = f(a, n, c);
			b = f(f(b, n, c), n, c);
		} while (gcd(abs(a - b), n) == 1);
		if (a != b)
			break;
	}
	lint x = gcd(abs(a - b), n);
	rec(x, v);
	rec(n / x, v);
}
vector<lint> factorize(lint n) {
	vector<lint> ret;
	rec(n, ret);
	sort(ret.begin(), ret.end());
	return ret;
}
lint euler_phi(lint n) {
	auto pf = factorize(n);
	pf.resize(unique(all(pf)) - pf.begin());
	for (auto &p : pf) {
		n -= n / p;
	}
	return n;
}