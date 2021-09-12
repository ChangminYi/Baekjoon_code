#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, cnt = 0;
vector<int> argi, series;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	argi.resize(n);
	for (int& i : argi) {
		cin >> i;
	}

	/*
	* O(nlogn)�� ���� �� �����ϴ� �κ� ���� ã��
	* � ���Ҹ� ��������� �� �ʿ䰡 ��� �ε��� �迭�� ����
	* ���� �� �����ϴ� �κ� ������ ���Ե��� ���� �����ٸ���
	* �߶󳻸� �ּ��� �������� �ڸ� �� ����
	*/
	series.push_back(argi[0]);
	for (int i = 1; i < n; i++) {
		if (series.back() < argi[i]) {
			series.push_back(argi[i]);
		}
		else {
			auto lb = lower_bound(series.begin(), series.end(), argi[i]);
			int tmp_idx = distance(series.begin(), lb);
			series[tmp_idx] = argi[i];
		}
	}

	cout << n - series.size();

	return 0;
}