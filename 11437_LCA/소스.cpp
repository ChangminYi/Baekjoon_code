#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	pair<int, int> temp;
	int N = 0;
	cin >> N;

	deque<deque<int>> tree(N + 1);
	deque<int> parent(N + 1, 0);
	deque<int> depth(N + 1, 1);
	for (int i = 0; i < N - 1; i++) {
		cin >> temp.first>>temp.second;
		tree[temp.first].push_back(temp.second);
		tree[temp.second].push_back(temp.first);
	}

	deque<pair<int, int>> que;
	parent[1] = -1;
	que.push_back(make_pair(1, 1));
	while (!que.empty()) {
		int cur = que.front().first;
		int curDep = que.front().second;
		que.pop_front();

		for (uint32_t i = 0; i < tree[cur].size(); i++) {
			if (parent[tree[cur][i]] == 0) {
				que.push_back(make_pair(tree[cur][i], curDep + 1));
				depth[tree[cur][i]] = depth[cur] + 1;
				parent[tree[cur][i]] = cur;
			}
		}
	}

	int M = 0;
	cin >> M;
	for (int iter = 0; iter < M; iter++) {
		cin >> temp.first >> temp.second;
		if (depth[temp.first] < depth[temp.second]) {
			swap(temp.first, temp.second);
		}

		while (depth[temp.first] != depth[temp.second]) {
			temp.first = parent[temp.first];
		}
		while (temp.first != temp.second) {
			temp.first = parent[temp.first];
			temp.second = parent[temp.second];
		}

		cout << temp.first << '\n';
	}

	return 0;
}