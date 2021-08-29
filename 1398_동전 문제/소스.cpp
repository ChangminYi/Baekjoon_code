#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lli;

const int INTERVAL = 100;
const uint32_t TEN = 10;
const uint32_t TWENTY_FIVE = 25;
vector<int> min_num(INTERVAL + 1, 0);

void init_min_val() {
	for (uint32_t i = 1; i < TEN; i++) {
		min_num[i] = min_num[i - 1] + 1;
	}
	for (uint32_t i = 10; i < TWENTY_FIVE; i++) {
		min_num[i] = min(min_num[i - 1], min_num[i - 10]) + 1;
	}
	for (uint32_t i = 25; i < min_num.size(); i++) {
		min_num[i] = min({ min_num[i - 1], min_num[i - 10], min_num[i - 25] }) + 1;
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	init_min_val();

	int testcase;
	cin >> testcase;
	do {
		lli n, res = 0;
		cin >> n;

		while (n > 0) {
			int frac = n % INTERVAL;
			res += min_num[frac];
			n /= INTERVAL;
		}

		cout << res << '\n';
	} while (--testcase > 0);

	return 0;
}