#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int64_t>> matrix;

matrix operator* (const matrix &a, const matrix &b) {
	matrix res(a.size(), vector<int64_t>(a.size()));
	for (uint32_t i = 0; i < a.size(); i++) {
		for (uint32_t j = 0; j < a.size(); j++) {
			for (uint32_t k = 0; k < a.size(); k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
			res[i][j] %= 1000;
		}
	}
	return res;
}


// O(logN) 시간에 제곱을 하는 알고리즘
matrix power(matrix a, int64_t n) {
	matrix res(a.size(), vector<int64_t>(a.size()));

	for (uint32_t i = 0; i < a.size(); i++) { // 단위 행렬
		res[i][i] = 1;
	}

	while (n > 0) {
		if (n % 2 == 1) {
			res = res * a;
		}
		n /= 2;
		a = a * a;
	}

	return res;
}

void PrintMatrix(const matrix& a) {
	for (uint32_t i = 0; i < a.size(); i++) {
		for (uint32_t j = 0; j < a.size(); j++) {
			cout << a[i][j] << ' ';
		}
		cout << '\n';
	}
}
int main(void) {
	cin.sync_with_stdio(false);
	cin.tie(nullptr);
	cout.sync_with_stdio(false);
	cout.tie(nullptr);

	int64_t n = 0, b = 0;
	cin >> n >> b;
	matrix a(n, vector<int64_t>(n));
	
	for (int64_t i = 0; i < n; i++) {
		for (int64_t j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	
	PrintMatrix(power(a, b));

	return 0;
}