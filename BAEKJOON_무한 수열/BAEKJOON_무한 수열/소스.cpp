#include <iostream>
#include <map>

using namespace std;
typedef long long lli;

map<lli, lli> dp = { make_pair(0, 1) };
lli p, q;

lli serial(lli index) {
	if (dp.find(index) == dp.end()) {
		lli frt = index / p;
		lli bak = index / q;

		dp.insert(make_pair(index, serial(frt) + serial(bak)));
	}

	return dp[index];
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	lli n;
	cin >> n >> p >> q;

	cout << serial(n);

	return 0;
}