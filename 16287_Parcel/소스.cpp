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
	* 배열을 두 부분으로 분할하여 살핀다.
	* 분할 기준점 인덱스 i를 설정한다.
	* argi[i] + argi[j] 값이 존재한다고 체크한다.
	* 기준점 바로 다음 i+1과 그 위의 인덱스 j의 합
	* tmp = argi[i+1] + argi[j] 계산하고, 범위 체크를 한다.
	* 만약 w-tmp 값이 체크가 되어 있다면 합이 있으므로 루프를 탈출.
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