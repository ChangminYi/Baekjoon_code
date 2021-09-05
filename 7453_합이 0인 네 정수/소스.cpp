#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lli;

int n;
lli cnt = 0;
vector<vector<int>> argi;
vector<int> sum_front, sum_back;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	argi.resize(n, vector<int>(4));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> argi[i][j];
		}
	}

	/*
	* a_i + b_i + c_i + d_i = 0의 형태를
	* 각각 a_i + b_i, c_i + d_i의 형태로 나누어 연산 줄이기
	* 후에 c_i + d_i의 결과만 정렬하여 이분 탐색 준비
	*/
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum_front.push_back(argi[i][0] + argi[j][1]);
			sum_back.push_back(argi[i][2] + argi[j][3]);
		}
	}
	sort(sum_back.begin(), sum_back.end());


	/*
	* a_i + b_i = -(c_i + d_i)인 모든 값 탐색
	* 같은 값이 중복하여 있을 수 있으므로,
	* upper_bound와 lower_bound 사용하여 개수 세기
	*/
	for (const int& i : sum_front) {
		int to_find = -1 * i;

		auto ub = upper_bound(sum_back.begin(), sum_back.end(), to_find);
		auto lb = lower_bound(sum_back.begin(), sum_back.end(), to_find);

		cnt += distance(lb, ub);
	}

	cout << cnt;

	return 0;
}