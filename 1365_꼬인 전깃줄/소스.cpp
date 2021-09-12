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
	* O(nlogn)의 가장 긴 증가하는 부분 수열 찾기
	* 어떤 원소를 지우는지는 알 필요가 없어서 인덱스 배열은 생략
	* 가장 긴 증가하는 부분 수열에 포함되지 않은 전깃줄만을
	* 잘라내면 최소의 전깃줄을 자를 수 있음
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