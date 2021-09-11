#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int testcase, n, ten_count;
vector<int> res;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> testcase;
	do {
		priority_queue<int, vector<int>, greater<int>> min_pq;
		priority_queue<int> max_pq;
		ten_count = 0;

		cin >> n;
		for (int i = 1, arg; i <= n; i++) {
			cin >> arg;

			max_pq.size() > min_pq.size() ? min_pq.push(arg) : max_pq.push(arg);

			if (!max_pq.empty() && !min_pq.empty()) {
				if (max_pq.top() > min_pq.top()) {
					int max_top = max_pq.top(), min_top = min_pq.top();
					max_pq.pop(), min_pq.pop();

					max_pq.push(min_top), min_pq.push(max_top);
				}
			}

			if (i & 1) {
				res.push_back(max_pq.top());
			}
		}

		cout << res.size() << '\n';
		for (int i = 1; i <= res.size(); i++) {
			cout << res[i - 1] << (i % 10 == 0 ? '\n' : ' ');
		}
		if (res.size() % 10 != 0) {
			cout << '\n';
		}
		res.clear();
	} while (--testcase > 0);

	return 0;
}