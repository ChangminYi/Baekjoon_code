#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n, cnt = 0;
vector<pint> arg;
vector<int> idx, seq;
priority_queue<int, vector<int>, greater<int>> res;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	arg.resize(n);
	idx.resize(n);
	for (pint& p : arg) {
		cin >> p.first >> p.second;
	}
	sort(arg.begin(), arg.end());

	seq.push_back(arg[0].second);
	for (int i = 1; i < n; i++) {
		if (seq.back() < arg[i].second) {
			seq.push_back(arg[i].second);
			idx[i] = ++cnt;
		}
		else {
			int tmp_idx = distance(seq.begin(), lower_bound(seq.begin(), seq.end(), arg[i].second));
			seq[tmp_idx] = arg[i].second;
			idx[i] = tmp_idx;
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		if (idx[i] == cnt) {
			cnt--;
		}
		else {
			res.push(arg[i].first);
		}
	}

	cout << res.size() << '\n';
	while (!res.empty()) {
		cout << res.top() << '\n';
		res.pop();
	}

	return 0;
}