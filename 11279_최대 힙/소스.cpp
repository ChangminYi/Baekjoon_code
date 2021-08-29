#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

bool comp(int a, int b) {
	return a > b;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	priority_queue<int, vector<int>, less<int>> que;
	int N = 0;
	cin >> N;

	for (int i = 0, temp = 0; i < N; i++) {
		cin >> temp;

		if (temp == 0) {
			if (que.empty()) {
				cout << 0 << '\n';
			}
			else {
				cout << que.top() << '\n';
				que.pop();
			}
		}
		else {
			que.push(temp);
		}
	}

	return 0;
}