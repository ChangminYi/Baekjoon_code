#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

const lli DIV = 1000000007;
const int MAX_SIZE = 2500;

vector<lli> dp(MAX_SIZE + 1, 0);

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	dp[0] = 1;
	for (int i = 1; i <= MAX_SIZE; i++) {
		for (int j = 0; j < i; j++) {
			dp[i] += dp[j] * dp[i - j - 1] % DIV;
		}
		dp[i] %= DIV;
	}

	int iter;
	cin >> iter;
	do {
		int n;
		cin >> n;

		if ((n & 1) == 1) {
			cout << 0 << '\n';
		}
		else {
			cout << dp[n / 2] << '\n';
		}
	} while (--iter > 0);

	return 0;
}