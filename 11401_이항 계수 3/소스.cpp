#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

const lli MOD = 1000000007L;
lli n, k;
vector<lli> fact_set;

lli fast_exp(lli base, lli exp) {
	lli ret = 1;
	while (exp > 0) {
		if (exp & 1) {
			ret = (ret * base) % MOD;
		}
		base = (base * base) % MOD;
		exp >>= 1;
	}
	return ret;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> k;
	fact_set = vector<lli>(n + 1, 1);
	for (int i = 1; i <= n; i++) {
		fact_set[i] = (i * fact_set[i - 1]) % MOD;
	}

	lli head = fact_set[n];
	lli base_left = fast_exp(fact_set[k], MOD - 2);
	lli base_right = fast_exp(fact_set[n - k], MOD - 2);
	cout << (head * ((base_left * base_right) % MOD)) % MOD;

	return 0;
}