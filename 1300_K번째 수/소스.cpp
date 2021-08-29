#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	int res = 0;
	int left = 1, right = k;
	while (left <= right) {
		int mid = (left + right) / 2;
		int lower_count = 0;

		for (int i = 1; i <= n; i++) {
			lower_count += min(n, mid / i);
		}

		if (lower_count < k) {
			left = mid + 1;
		}
		else {
			res = mid;
			right = mid - 1;
		}
	}

	cout << res;

	return 0;
}