#include <iostream>
#include <deque>
#include <cmath>
#include <climits>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;

	deque<int> argi(n);
	for (int& i : argi) {
		cin >> i;
	}

	int min_sum = INT32_MAX;
	pair<int, int> p;
	while (argi.size() > 1) {
		int tmp_sum = argi.front() + argi.back();

		if (abs(tmp_sum) < min_sum) {
			min_sum = abs(tmp_sum);
			p.first = argi.front();
			p.second = argi.back();
		}

		if (tmp_sum == 0) {
			break;
		}
		else if (tmp_sum < 0) {
			argi.pop_front();
		}
		else {
			argi.pop_back();
		}
	}

	cout << p.first << ' ' << p.second;

	return 0;
}