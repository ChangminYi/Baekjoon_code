#include <iostream>

using namespace std;
typedef long long lli;

lli sum(lli to_cnt) {
	lli ret = 0;
	for (int i = 0; i < 55; i++) {
		ret += (to_cnt + 1 >> i + 1 << i)
			+ max(0LL, (to_cnt + 1) % (1LL << i + 1) - (1LL << i));
	}
	return ret;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	lli a, b;
	cin >> a >> b;

	cout << sum(b) - sum(a - 1);

	return 0;
}