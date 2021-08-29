#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;
	vector<pint> line(n);
	for (pint& p : line) {
		cin >> p.first >> p.second;
	}
	sort(line.begin(), line.end());

	int res = 1;
	priority_queue<int, vector<int>, greater<int>> pq;
	pq.push(line.front().second);
	for (int i = 1; i < n; i++) {
		while (!pq.empty() && pq.top() <= line[i].first) {
			pq.pop();
		}
		pq.push(line[i].second);

		res = max<int>(res, pq.size());
	}

	cout << res;

	return 0;
}