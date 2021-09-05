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
	* a_i + b_i + c_i + d_i = 0�� ���¸�
	* ���� a_i + b_i, c_i + d_i�� ���·� ������ ���� ���̱�
	* �Ŀ� c_i + d_i�� ����� �����Ͽ� �̺� Ž�� �غ�
	*/
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum_front.push_back(argi[i][0] + argi[j][1]);
			sum_back.push_back(argi[i][2] + argi[j][3]);
		}
	}
	sort(sum_back.begin(), sum_back.end());


	/*
	* a_i + b_i = -(c_i + d_i)�� ��� �� Ž��
	* ���� ���� �ߺ��Ͽ� ���� �� �����Ƿ�,
	* upper_bound�� lower_bound ����Ͽ� ���� ����
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