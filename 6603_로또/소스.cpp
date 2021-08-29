#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N = 0;
	while (true) {
		cin >> N;
		if (N == 0) { break; }

		vector<int> number(N);
		for (int &i : number) {
			cin >> i;
		}
		sort(number.begin(), number.end());
		vector<bool> check(N, false);
		for (int i = 0; i < 6; i++) {
			check[i] = true;
		}

		do {
			for (int i = 0; i < N; i++) {
				if (check[i] == true) {
					cout << number[i] << ' ';
				}
			}
			cout << '\n';
		} while (prev_permutation(check.begin(), check.end()));
		cout << '\n';
	}

	return 0;
}