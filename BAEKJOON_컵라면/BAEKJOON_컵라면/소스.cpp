#include <iostream>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct NODE {
	int deadline;
	int value;
}node;

bool operator<(const node& a, const node& b) {
	if (a.deadline == b.deadline) {
		return a.value < b.value;
	}
	return a.deadline < b.deadline;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, max_day = 0;
	cin >> n;
	deque<node> dat(n);
	for (node& n : dat) {
		cin >> n.deadline >> n.value;
		max_day = max(n.deadline, max_day);
	}
	sort(dat.rbegin(), dat.rend());

	int max_sum = 0;
	priority_queue<int> pq;
	for (int i = max_day; i >= 1; i--) {
		while (!dat.empty() && dat.front().deadline == i) {
			pq.push(dat.front().value);
			dat.pop_front();
		}

		if (!pq.empty()) {
			max_sum += pq.top();
			pq.pop();
		}
	}

	cout << max_sum;

	return 0;
}