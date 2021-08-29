#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	priority_queue<int, vector<int>, greater<int>> pq;
	uint32_t N = 0;
	cin >> N;

	for (uint32_t i = 0; i < N; i++) {
		int temp = 0;
		cin >> temp;

		if (temp == 0) {
			if (pq.empty()) { cout << 0 << '\n'; }
			else {
				cout << pq.top() << '\n';
				pq.pop();
			}
		}
		else {
			pq.push(temp);
		}
	}

	return 0;
}