#include <iostream>

using namespace std;
typedef long long lli;

const lli DIV = 1000000007;
const lli MAX_SIZE = 4000001;
lli facto[MAX_SIZE];
lli inverse[MAX_SIZE];

lli fast_exp(lli x, lli a) {
	lli ret = 1;
	while (a > 0) {
		if (a % 2 == 1) {
			ret = ret * x % DIV;
		}
		x = x * x % DIV;
		a /= 2;
	}
	return ret;
}

lli combi(lli n, lli k) {
	return (((facto[n] * inverse[k]) % DIV) * inverse[n - k]) % DIV;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	facto[0] = 1;
	for (lli i = 1; i < MAX_SIZE; i++) {
		facto[i] = facto[i - 1] * i % DIV;
	}
	inverse[MAX_SIZE - 1] = fast_exp(facto[MAX_SIZE - 1], DIV - 2);
	for (lli i = MAX_SIZE - 2; i >= 0; i--) {
		inverse[i] = inverse[i + 1] * (i + 1) % DIV;
	}

	int iter;
	cin >> iter;
	do {
		int n, k;
		cin >> n >> k;
		cout << combi(n, k) << '\n';
	} while (--iter > 0);

	return 0;
}