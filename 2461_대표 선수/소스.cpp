#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <limits>

using namespace std;

typedef pair<int, int> pint;

int n, m;
vector<vector<int>> argi;
vector<int> idx;
priority_queue<pint, vector<pint>, greater<pint>> pq;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	argi = vector<vector<int>>(n, vector<int>(m));
	idx = vector<int>(n, 1);
	for (vector<int>& row : argi) {
		for (int& i : row) {
			cin >> i;
		}
		sort(row.begin(), row.end());
	}

	int max_val = 0;
	for (int i = 0; i < n; i++) {
		max_val = max(max_val, argi[i][0]);
		pq.push(make_pair(argi[i][0], i));
	}

	int res = INT32_MAX;
	for (int i = 0; i < n * (m - 1); i++) {
		int cur_val = pq.top().first;
		int cur_idx = pq.top().second;
		pq.pop();

		res = min(res, max_val - cur_val);
		if (idx[cur_idx] == m) {
			break;
		}
		else {
			max_val = max(max_val, argi[cur_idx][idx[cur_idx]]);
			pq.push(make_pair(argi[cur_idx][idx[cur_idx]], cur_idx));
			idx[cur_idx]++;
		}
	}

	cout << res;

	return 0;
}