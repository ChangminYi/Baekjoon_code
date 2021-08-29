#include <iostream>
#include <deque>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long lli;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;

	deque<lli> argi(n);
	for (lli& i : argi) {
		cin >> i;
	}
	sort(argi.begin(), argi.end());

	lli min_sum = LLONG_MAX;
	lli res[3] = { 0, 0, 0 };
	for (uint32_t i = 0, j, k; i < argi.size() - 2; i++) {
		j = i + 1;
		k = argi.size() - 1;
		
		bool break_flag = false;
		while (j < k && j < argi.size() && k > i) {
			lli tmp_sum = argi[i] + argi[j] + argi[k];

			if (abs(tmp_sum) < min_sum) {
				min_sum = abs(tmp_sum);
				res[0] = argi[i];
				res[1] = argi[j];
				res[2] = argi[k];
			}

			if (tmp_sum == 0) {
				break_flag = true;
				break;
			}
			else if (tmp_sum > 0) {
				k--;
			}
			else {
				j++;
			}
		}

		if (break_flag) {
			break;
		}
	}

	cout << res[0] << ' ' << res[1] << ' ' << res[2];

	return 0;
}