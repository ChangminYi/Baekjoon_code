#include <iostream>
#include <deque>
#include <climits>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, base_sum;
	cin >> n >> base_sum;
	deque<int> argi(n);
	for (int& i : argi) {
		cin >> i;
	}

	int min_len = INT32_MAX;
	int temp_sum = 0;
	deque<int> temp_argi;
	while (!argi.empty()) {
		if (temp_sum < base_sum) {
			temp_sum += argi.front();
			temp_argi.push_back(argi.front());
			argi.pop_front();
		}

		if (temp_sum >= base_sum) {
			min_len = min<int>(min_len, temp_argi.size());

			temp_sum -= temp_argi.front();
			temp_argi.pop_front();
		}
	}
	while (temp_sum >= base_sum) {
		min_len = min<int>(min_len, temp_argi.size());

		temp_sum -= temp_argi.front();
		temp_argi.pop_front();
	}

	if (min_len == INT32_MAX) {
		cout << 0;
	}
	else {
		cout << min_len;
	}

	return 0;
}