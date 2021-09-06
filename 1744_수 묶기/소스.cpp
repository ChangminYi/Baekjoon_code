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
		// ���� Ȥ�� 0�� ���� ���ϸ� 0 �̻����� �ٲ� �� ����
		if (argi[lo] <= 0 && argi[lo + 1] <= 0) {
			sum += (lli)argi[lo] * argi[lo + 1];
			lo += 2;
		}
		else {
			break;
		}
	}
	while (hi > 0) {
		// ���Ͽ� Ŀ���� ���鸸 ���ؼ� ���ϱ�
		if (1 < argi[hi - 1] && 1 < argi[hi]) {
			sum += (lli)argi[hi - 1] * argi[hi];
			hi -= 2;
		}
		else {
			break;
		}
	}
	while (lo <= hi) {
		//ó������ ���� ���� ó��
		sum += argi[hi--];
	}
	
	cout << sum;

	return 0;
}