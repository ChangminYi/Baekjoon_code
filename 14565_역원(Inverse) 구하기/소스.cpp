#include <iostream>
#include <numeric>
#include <tuple>

using namespace std;

typedef long long lli;
typedef tuple<lli, lli, lli> plli;

lli get_add_inverse(lli a, lli mod) {
	return mod - a;
}

plli ext_gcd(lli a, lli b) {
	if (b == 0) {
		return make_tuple(a, 1, 0);
	}
	else {
		plli tmp = ext_gcd(b, a % b);
		return make_tuple(get<0>(tmp), get<2>(tmp), get<1>(tmp) - (a / b) * get<2>(tmp));
	}
}

lli get_mult_inverse(lli a, lli mod) {
	if (gcd(a, mod) > 1) {
		return -1;
	}
	else {
		return (get<2>(ext_gcd(mod, a)) + mod) % mod;
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	lli n, a;
	cin >> n >> a;

	cout << get_add_inverse(a, n) << ' ' << get_mult_inverse(a, n);

	return 0;
}