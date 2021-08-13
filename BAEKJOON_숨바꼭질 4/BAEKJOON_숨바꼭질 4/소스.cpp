#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

const int MAX = 100001;
const int NOT_VISIT = -1;

int n, k;
vector<int> min_time(MAX, NOT_VISIT);
vector<int> parent(MAX, NOT_VISIT);
stack<int> trace;
queue<int> que;

bool in_range(int x) {
	return (0 <= x && x < MAX);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> k;

	min_time[n] = 0;
	parent[n] = n;
	que.push(n);
	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		if (cur == k) {
			break;
		}
		else {
			if (in_range(cur + 1) && min_time[cur + 1] == NOT_VISIT) {
				parent[cur + 1] = cur;
				min_time[cur + 1] = min_time[cur] + 1;
				que.push(cur + 1);
			}
			if (in_range(cur - 1) && min_time[cur - 1] == NOT_VISIT) {
				parent[cur - 1] = cur;
				min_time[cur - 1] = min_time[cur] + 1;
				que.push(cur - 1);
			}
			if (in_range(2 * cur) && min_time[2 * cur] == NOT_VISIT) {
				parent[2 * cur] = cur;
				min_time[2 * cur] = min_time[cur] + 1;
				que.push(2 * cur);

			}
		}
	}

	trace.push(k);
	while (parent[trace.top()] != trace.top()) {
		trace.push(parent[trace.top()]);
	}

	cout << min_time[k] << '\n';
	while (!trace.empty()) {
		cout << trace.top() << ' ';
		trace.pop();
	}

	return 0;
}