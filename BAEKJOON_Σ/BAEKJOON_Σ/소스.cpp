#include <iostream>
#include <numeric>

using namespace std;

typedef long long lli;

const lli MOD = 1000000007;

lli fast_exp(lli a, lli x) {
	lli ret = 1;

	for (int i = 0; i < 64; i++) {
		if (x & 1) {
			ret = (a * ret) % MOD;
		}
		a = (a * a) % MOD;
		x >>= 1;
	}

	return ret;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int iter;
	cin >> iter;

	lli sum = 0;
	do {
		int n, s, g;
		cin >> n >> s;

		g = gcd(n, s);
		n /= g, s /= g;

		sum += (s * fast_exp(n, MOD - 2)) % MOD;
		sum %= MOD;
	} while (--iter > 0);

	cout << sum;

	return 0;
}