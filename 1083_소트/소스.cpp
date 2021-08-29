#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, k;
	cin >> n;
	vector<int> argi(n);
	for (int& i : argi) {
		cin >> i;
	}
	cin >> k;

	for (int i = 0; i < n; i++) {
		int max_val = -1, max_ind = 0;

		for (int j = i; j <= min(n - 1, i + k); j++) {
			if (max_val < argi[j]) {
				max_val = argi[j];
				max_ind = j;
			}
		}

		k -= (max_ind - i);
		for (int j = max_ind; j > i; j--) {
			swap(argi[j - 1], argi[j]);
		}

		if (k <= 0) {
			break;
		}
	}

	for (int& i : argi) {
		cout << i << ' ';
	}

	return 0;
}