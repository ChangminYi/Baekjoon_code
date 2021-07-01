#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

const lli DIV = 1000000007;

vector<vector<lli>> operator* (const vector<vector<lli>>& a, const vector<vector<lli>>& b) {
	vector<vector<lli>> res(2, vector<lli>(2));

	res[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % DIV;
	res[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % DIV;
	res[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % DIV;
	res[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % DIV;
	
	return res;
}

vector<vector<lli>> fast_expo(vector<vector<lli>> base, lli expo) {
	if (expo == 0) {
		return { {1, 0}, {0, 1} };
	}
	else if (expo == 1) {
		return base;
	}
	else {
		vector<vector<lli>> sub_m = fast_expo(base, expo / 2);
		sub_m = sub_m * sub_m;
		if (expo % 2 == 1) {
			sub_m = sub_m * base;
		}

		return sub_m;
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	lli n;
	cin >> n;

	vector<vector<lli>> tmp = {
		{1, 1},
		{1, 0}
	};
	vector<vector<lli>> res = fast_expo(tmp, --n);
	cout << res[0][0];

	return 0;
}