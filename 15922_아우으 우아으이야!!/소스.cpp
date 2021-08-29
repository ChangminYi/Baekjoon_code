#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	deque<pair<int, int>> lines(1);
	int n;
	cin >> n;

	cin >> lines.front().first >> lines.front().second;
	for (int i = 0; i < n - 1; i++) {
		pair<int, int> temp;
		cin >> temp.first >> temp.second;

		if (lines.back().first <= temp.first && temp.first <= lines.back().second) {
			lines.back().second = max(lines.back().second, temp.second);
		}
		else {
			lines.push_back(temp);
		}
	}

	long long sum = 0;
	for (pair<int, int>& p : lines) {
		sum += (long long)p.second - p.first;
	}

	cout << sum;

	return 0;
}