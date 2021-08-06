#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> argi(n);
	for (int& i : argi) {
		cin >> i;
	}

	if (n < 3) {
		if (n == 2 && argi[1] == argi[0]) {
			cout << argi[1];
		}
		else {
			cout << 'A';
		}
	}
	else {
		int a, b;

		if (argi[1] == argi[0]) {
			if (argi[2] == argi[1]) {
				a = 1;
				b = 0;
			}
			else {
				cout << 'B';
				return 0;
			}
		}
		else {
			a = (argi[2] - argi[1]) / (argi[1] - argi[0]);
			b = argi[1] - (argi[0] * a);
		}

		int right_value = true;
		for (int i = 0; i < n - 1; i++) {
			if (argi[i] * a + b != argi[i + 1]) {
				right_value = false;
				break;
			}
		}

		if (right_value) {
			cout << argi.back() * a + b;
		}
		else {
			cout << 'B';
		}
	}

	return 0;
}