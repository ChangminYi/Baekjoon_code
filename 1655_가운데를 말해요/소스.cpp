#include <iostream>
#include <queue>
#include <functional>

using namespace std;

priority_queue<int, vector<int>, greater<int>> min_pq;
priority_queue<int, vector<int>, less<int>> max_pq;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	do {
		int num;
		cin >> num;

		max_pq.size() > min_pq.size() ? min_pq.push(num) : max_pq.push(num);

		if (!max_pq.empty() && !min_pq.empty()) {
			if (max_pq.top() > min_pq.top()) {
				int max_val = max_pq.top();
				int min_val = min_pq.top();
				max_pq.pop();
				min_pq.pop();

				max_pq.push(min_val);
				min_pq.push(max_val);
			}
		}

		cout << max_pq.top() << '\n';
	} while (--n > 0);

	return 0;
}