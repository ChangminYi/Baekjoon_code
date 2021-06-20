#include <iostream>
#include <deque>

using namespace std;

typedef long long ll;

ll comb_with_rept(int p, int q) {
	ll res = 1;
	deque<int> hi, lo;
	if (p < q) {
		swap(p, q);
	}


	for (int i = p + q; i >= 1; i--) {
		hi.push_back(i);
	}
	for (int i = 1; i <= p; i++) {
		lo.push_back(i);
	}
	for (int i = 1; i <= q; i++) {
		lo.push_back(i);
	}

	while (!hi.empty()) {
		res *= hi.front();
		res /= lo.front();
		hi.pop_front();
		lo.pop_front();
	}

	return res;
}

int main() {
	int row = 0, col = 0, K = 0;
	cin >> row >> col >> K;

	if (K == 0) {
		cout << comb_with_rept(row - 1, col - 1);
	}
	else {
		K--;
		int row_first = K / col;
		int col_first = K % col;
		int row_second = (row - 1) - row_first;
		int col_second = (col - 1) - col_first;

		cout << comb_with_rept(row_first, col_first) * comb_with_rept(row_second, col_second);
	}

	return 0;
}