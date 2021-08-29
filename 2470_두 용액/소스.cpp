#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> argi(n);
	for (int& i : argi) {
		cin >> i;
	}
	sort(argi.begin(), argi.end());

	int min_dist = INT32_MAX;
	int left = 0, right = n - 1;
	int min_lo = argi[left], min_hi = argi[right];
	while (left < right) {
		int tmp_sum = argi[left] + argi[right];

		if (abs(tmp_sum) < min_dist) {
			min_dist = abs(tmp_sum);
			min_lo = argi[left];
			min_hi = argi[right];
		}

		if (tmp_sum < 0) {
			left++;
		}
		else if(tmp_sum > 0) {
			right--;
		}
		else {
			break;
		}
	}

	cout << min_lo << ' ' << min_hi;

	return 0;
}