#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

vector<vector<int>> graph;
vector<bool> visit;

bool bfs(int root) {
	bool res = true;
	queue<pint> que, to_delete;

	que.push(make_pair(root, 0));
	visit[root] = true;
	while (!que.empty()) {
		int cur = que.front().first;
		int from = que.front().second;
		que.pop();

		for (int& nxt : graph[cur]) {
			if (nxt == from) {
				continue;
			}
			else {
				if (!visit[nxt]) {
					visit[nxt] = true;
					que.push(make_pair(nxt, cur));
				}
				else {
					res = false;
				}
			}
		}

		/*for (int nxt : graph[cur]) {
			to_delete.push(nxt);

			if (!visit[nxt]) {
				visit[nxt] = true;
				que.push(nxt);
			}
			else {
				res = false;
			}
		}

		while (!to_delete.empty()) {
			int nxt = to_delete.front();
			to_delete.pop();

			graph[cur].erase(find(graph[cur].begin(), graph[cur].end(), nxt));
			graph[nxt].erase(find(graph[nxt].begin(), graph[nxt].end(), cur));
		}*/
	}

	return res;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n, m, cnt = 1;
	while (true) {
		cin >> n >> m;

		if (n == 0 && m == 0) {
			break;
		}
		else {
			graph = vector<vector<int>>(n + 1, vector<int>());
			visit = vector<bool>(n + 1, false);

			for (int i = 0, arg1, arg2; i < m; i++) {
				cin >> arg1 >> arg2;
				graph[arg1].push_back(arg2);
				graph[arg2].push_back(arg1);
			}

			int tree_num = 0;
			for (int i = 1; i <= n; i++) {
				if (!visit[i]) {
					if (bfs(i)) {
						tree_num++;
					}
				}
			}

			cout << "Case " << cnt++ << ": ";
			switch (tree_num) {
			case 0:
				cout << "No trees.\n";
				break;
			case 1:
				cout << "There is one tree.\n";
				break;
			default:
				cout << "A forest of " << tree_num << " trees.\n";
				break;
			}
		}
	}
	
	return 0;
}