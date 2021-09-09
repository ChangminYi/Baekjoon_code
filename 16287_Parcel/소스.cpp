#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SUM = 400000;

int w, n;
bool ans_found = false;
vector<int> argi;
vector<bool> weight_exist(MAX_SUM + 1, false);

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> w >> n;
	argi.resize(n);
	for (int& i : argi) {
		cin >> i;
	}
	sort(argi.begin(), argi.end());

	/*
	* �迭�� �� �κ����� �����Ͽ� ���ɴ�.
	* ���� ������ �ε��� i�� �����Ѵ�.
	* argi[i] + argi[j] ���� �����Ѵٰ� üũ�Ѵ�.
	* ������ �ٷ� ���� i+1�� �� ���� �ε��� j�� ��
	* tmp = argi[i+1] + argi[j] ����ϰ�, ���� üũ�� �Ѵ�.
	* ���� w-tmp ���� üũ�� �Ǿ� �ִٸ� ���� �����Ƿ� ������ Ż��.
	*/
	for (int i = 1; i < n - 2 && !ans_found; i++) {
		for (int j = 0; j < i; j++) {
			weight_exist[argi[i] + argi[j]] = true;
		}

		for (int j = i + 2, tmp; j < n; j++) {
			tmp = w - (argi[i + 1] + argi[j]);

			if (0 < tmp && tmp <= MAX_SUM) {
				if (weight_exist[tmp]) {
					ans_found = true;
					break;
				}
			}
		}
	}

	cout << (ans_found ? "YES" : "NO");

	return 0;
}