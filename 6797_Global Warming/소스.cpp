#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> argi;
vector<int> patt;

bool find_pattern(int interval) {
	for (int i = 0; i < n - 1; i++) {
		if (patt[i] != patt[i % interval]) {
			return false;
		}
	}

	return true;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	while (true) {
		cin >> n;

		if (n == 0) {
			break;
		}
		else {
			argi.resize(n);
			patt.resize(n - 1);

			for (int& i : argi) {
				cin >> i;
			}

			if (n == 1) {
				cout << 0 << '\n';
			}
			else {
				for (int i = 0; i < n - 1; i++) {
					patt[i] = argi[i + 1] - argi[i];
				}

				for (int i = 1; i <= n - 1; i++) {
					if (find_pattern(i)) {
						cout << i << '\n';
						break;
					}
				}
			}
		}
	}

	return 0;
}