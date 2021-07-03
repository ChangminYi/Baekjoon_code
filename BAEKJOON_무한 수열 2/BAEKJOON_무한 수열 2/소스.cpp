#include <iostream>
#include <unordered_map>

using namespace std;

typedef long long lli;

unordered_map<lli, lli> dp;
lli P, Q, X, Y;

lli get_serial(lli N) {
	if (N <= 0) {
		return 1;
	}
	else {
		if (dp.find(N) == dp.end()) {
			dp[N] = get_serial(N / P - X) + get_serial(N / Q - Y);
		}

		return dp[N];
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	lli N;
	cin >> N >> P >> Q >> X >> Y;

	cout << get_serial(N);

	return 0;
}