#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lli;

int n;
lli sum = 0;
vector<int> argi;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	argi.resize(n);
	for (int& i : argi) {
		cin >> i;
	}
	sort(argi.begin(), argi.end());

	int lo = 0, hi = n - 1;
	while (lo < hi) {
		// 음수 혹은 0을 서로 곱하면 0 이상으로 바꿀 수 있음
		if (argi[lo] <= 0 && argi[lo + 1] <= 0) {
			sum += (lli)argi[lo] * argi[lo + 1];
			lo += 2;
		}
		else {
			break;
		}
	}
	while (hi > 0) {
		// 곱하여 커지는 값들만 곱해서 더하기
		if (1 < argi[hi - 1] && 1 < argi[hi]) {
			sum += (lli)argi[hi - 1] * argi[hi];
			hi -= 2;
		}
		else {
			break;
		}
	}
	while (lo <= hi) {
		//처리되지 않은 값들 처리
		sum += argi[hi--];
	}
	
	cout << sum;

	return 0;
}