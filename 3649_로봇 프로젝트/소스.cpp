#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, len;
vector<int> argi;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	while (cin >> len) {
		len *= 10000000;

		cin >> n;
		argi.resize(n);
		for (int& i : argi) {
			cin >> i;
		}

		sort(argi.begin(), argi.end());

		bool found = false;
		int lo = 0, hi = n - 1;
		while (lo < hi) {
			if (argi[lo] + argi[hi] == len) {
				found = true;
				break;
			}
			else {
				argi[lo] + argi[hi] < len ? lo++ : hi--;
			}
		}

		if (found) {
			cout << "yes " << argi[lo] << ' ' << argi[hi] << '\n';
		}
		else {
			cout << "danger\n";
		}
	}

	return 0;
}