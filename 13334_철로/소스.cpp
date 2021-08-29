#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

const int MAX_SIZE = 100000;
vector<pint> lines(MAX_SIZE);

bool pint_cmp(const pint& a, const pint& b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, d;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> lines[i].first >> lines[i].second;
		if (lines[i].first > lines[i].second) {
			swap(lines[i].first, lines[i].second);
		}
	}
	cin >> d;
	sort(lines.begin(), lines.begin() + n, pint_cmp);

	int max_count = 0;
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0, lft, rgt; i < n; i++) {
		lft = lines[i].first;
		rgt = lines[i].second;

		if (rgt - lft <= d) {
			pq.push(lft);

			while (!pq.empty()) {
				int cur = pq.top();
				
				if (rgt - cur <= d) {
					break;
				}
				else {
					pq.pop();
				}
			}

			max_count = max<int>(max_count, pq.size());
		}
	}

	cout << max_count;

	return 0;
}