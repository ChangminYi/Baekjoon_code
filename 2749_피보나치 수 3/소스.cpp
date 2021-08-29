#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;
typedef vector<vector<lli>> mtx;

const lli DIV = 1000000;

mtx operator*(const mtx& a, const mtx& b) {
	mtx ret = mtx(2, vector<lli>(2));

	ret[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % DIV;
	ret[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % DIV;
	ret[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % DIV;
	ret[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % DIV;

	return ret;
}

mtx fib(lli n, mtx m) {
	mtx ret = { {1, 0}, {0, 1} };
	switch (n) {
	case 0:
		return ret;
	case 1:
		return m;
	default:
		ret = fib(n / 2, m);
		ret = ret * ret;
		if (n & 1) {
			ret = ret * m;
		}
		return ret;
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	lli n;
	cin >> n;
	mtx matrix = mtx(2, vector<lli>(2, 1));
	matrix[1][1] = 0;

	cout << fib(--n, matrix)[0][0];

	return 0;
}