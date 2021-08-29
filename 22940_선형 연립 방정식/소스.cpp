#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

typedef long long lli;

int n;
vector<vector<lli>> linear;

void mult(int a, int b) {
	lli mult_a = lcm(linear[a][a], linear[b][a]) / linear[a][a];
	lli mult_b = lcm(linear[a][a], linear[b][a]) / linear[b][a];
	for (int i = 0; i <= n; i++) {
		linear[a][i] *= mult_a;
		linear[b][i] *= mult_b;
	}
}

void sub(int a, int b) {
	for (int i = 0; i <= n; i++) {
		linear[b][i] = linear[a][i] - linear[b][i];
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	linear = vector<vector<lli>>(n, vector<lli>(n + 1));
	for (vector<lli>& row : linear) {
		for (lli& i : row) {
			cin >> i;
		}
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			mult(i, j);
			sub(i, j);
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j > i; j--) {
			linear[i][n] -= linear[i][j] * linear[j][n];
			linear[i][j] = 0;
		}
		linear[i][n] /= linear[i][i];
		linear[i][i] = 1;
	}

	for (int i = 0; i < n; i++) {
		cout << linear[i][n] << ' ';
	}

	return 0;
}