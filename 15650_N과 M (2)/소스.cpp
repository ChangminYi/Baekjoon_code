#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N = 0, M = 0;
	cin >> N >> M;

	vector<bool> table = vector<bool>(N, false);
	for (int i = 0; i < M; i++) { table[i] = true; }
	do {
		for (int i = 0; i < N; i++) {
			if (table[i]) { cout << i + 1 << ' '; }
		}
		cout << '\n';
	} while (prev_permutation(table.begin(), table.end()));

	return 0;
}