#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int testcase;
	cin >> testcase;
	do {
		int n;
		cin >> n;
		vector<int> graph(n+1);
		vector<bool> visit(n + 1, false);
		vector<bool> finish(n + 1, false);
		for (int i = 1; i <= n; i++) {
			cin >> graph[i];
		}

		int cnt = n;
		stack<int> stk;
		for (int i = 1; i <= n; i++) {
			if (!visit[i]) {
				visit[i] = true;
				stk.push(i);

				int nxt = graph[i];
				while (true) {
					if (!visit[nxt]) {
						visit[nxt] = true;
						stk.push(nxt);
						nxt = graph[nxt];
						continue;
					}
					else if (!finish[nxt]) {
						while (stk.top() != nxt) {
							finish[stk.top()] = true;
							stk.pop();
							cnt--;
						}
						finish[stk.top()] = true;
						stk.pop();
						cnt--;
					}
				
					while (!stk.empty()) {
						finish[stk.top()] = true;
						stk.pop();
					}
					break;
				}
			}
		}

		cout << cnt << '\n';
	} while (--testcase > 0);

	return 0;
}