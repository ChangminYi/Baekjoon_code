#include <iostream>

using namespace std;

typedef long long lli;

lli a, r, n, mod;

lli fast_exp(lli base, lli exp) {
	if (exp == 0) {
		return 1;
	}
	else {
		lli tmp = fast_exp(base, exp / 2);
		tmp = (tmp * tmp) % mod;
		if (exp & 1) {
			tmp = (tmp * base) % mod;
		}
		return tmp;
	}
}

lli get_sum(lli exp) {
	if (exp == 0) {
		return 1;
	}
	else if (exp == 1) {
		return (r + 1) % mod;
	}
	else {
		if (exp % 2 == 0) {
			lli left = get_sum(exp / 2 - 1) * (fast_exp(r, exp / 2) + 1) % mod;
			lli right = fast_exp(r, exp);
			return (left + right) % mod;
		}
		else {
			lli left = get_sum(exp / 2);
			lli right = fast_exp(r, exp / 2 + 1) + 1;
			return left * right % mod;
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> a >> r >> n >> mod;

	cout << a * get_sum(n - 1) % mod;

	return 0;
}