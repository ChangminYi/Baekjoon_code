#include <iostream>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, max_day = 0;
	cin >> n;
	deque<pint> arg(n);
	//first가 날짜(d), second가 값(p)
	for (pint& p : arg) {
		cin >> p.second >> p.first;
		max_day = max(max_day, p.first);
	}
	sort(arg.begin(), arg.end());

	long long sum = 0;
	priority_queue<pint> pq;
	for (int i = max_day; i > 0; i--) {
		while (!arg.empty() && arg.back().first == i) {
			pq.push(make_pair(arg.back().second, arg.back().first));
			arg.pop_back();
		}

		while (!pq.empty()) {
			if (pq.top().second >= i) {
				sum += pq.top().first;
				pq.pop();
				break;
			}
			else {
				pq.pop();
			}
		}
	}

	cout << sum;

	return 0;
}