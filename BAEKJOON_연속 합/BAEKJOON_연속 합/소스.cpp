#include <iostream>
#include <cmath>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int test_num;
	cin >> test_num;
	while (test_num-- > 0) {
		long long to_search;
		cin >> to_search;

		long long ans_cnt = 0;
		long long sch_max = sqrt(2 * to_search);
		while (sch_max * (sch_max + 1) < 2 * to_search) {
			sch_max++;
		}
		for (long long i = 2; i <= sch_max; i++) {
			long long min_sum = i * (i + 1) / 2;

			if ((to_search - min_sum) % i == 0) {
				ans_cnt++;
			}
		}

		cout << ans_cnt << '\n';
	}

	return 0;
}