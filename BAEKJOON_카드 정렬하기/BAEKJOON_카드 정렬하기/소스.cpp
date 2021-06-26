#include <iostream>
#include <queue>
#include <functional>

using namespace std;

typedef long long lli;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	priority_queue<lli, vector<lli>, greater<lli>> pq;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		lli temp;
		cin >> temp;
		pq.push(temp);
	}

	lli sum = 0;
	while (true) {
		lli frt = pq.top();
		pq.pop();

		if (pq.empty()) {
			break;
		}
		else {
			lli temp = pq.top() + frt;
			pq.pop();

			sum += temp;
			pq.push(temp);
		}
	}

	cout << sum;

	return 0;
}