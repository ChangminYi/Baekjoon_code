#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);
	
	int n, m;
	cin >> n >> m;
	vector<int> degree = vector<int>(n + 1, 0);
	vector<vector<int>> graph = vector<vector<int>>(n + 1);
	for (int i = 0, num; i < m; i++) {
		cin >> num;
		vector<int> tmp(num);
		for (int& i : tmp) {
			cin >> i;
		}

		for (uint32_t i = 0; i < tmp.size() - 1; i++) {
			degree[tmp[i + 1]]++;
			graph[tmp[i]].push_back(tmp[i + 1]);
		}
	}

	vector<int> res;
	queue<int> que;
	vector<bool> visit = vector<bool>(n + 1, false);
	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0) {
			que.push(i);
			visit[i] = true;
		}
	}
	while (!que.empty()) {
		int cur = que.front();
		res.push_back(cur);
		que.pop();

		for (int& i : graph[cur]) {
			degree[i]--;

			if (degree[i] == 0) {
				visit[i] = true;
				que.push(i);
			}
		}

	}

	if (res.size() < n) {
		cout << 0;
	}
	else {
		for (int& i : res) {
			cout << i << '\n';
		}
	}

	return 0;
}