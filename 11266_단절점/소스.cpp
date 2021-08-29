#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<bool> is_cut;
vector<int> discov;
int visit_cnt = 0;

int dfs(int cur, bool is_root) {
	discov[cur] = ++visit_cnt;
	int ret = discov[cur];

	int child = 0;
	for (int& nxt : graph[cur]) {
		if (discov[nxt] == 0) {
			child++;

			int lo_val = dfs(nxt, false);
			if (!is_root && lo_val >= discov[cur]) {
				is_cut[cur] = true;
			}
			ret = min(ret, lo_val);
		}
		else {
			ret = min(ret, discov[nxt]);
		}
	}

	if (is_root) {
		is_cut[cur] = (child >= 2);
	}
	return ret;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int v, e;
	cin >> v >> e;
	graph = vector<vector<int>>(v + 1);
	is_cut = vector<bool>(v + 1, false);
	discov = vector<int>(v + 1, 0);
	for (int i = 0, arg1, arg2; i < e; i++) {
		cin >> arg1 >> arg2;
		graph[arg1].push_back(arg2);
		graph[arg2].push_back(arg1);
	}

	for (int i = 1; i <= v; i++) {
		if (discov[i] == 0) {
			dfs(i, true);
		}
	}

	int ret_cnt = 0;
	for (int i = 1; i <= v; i++) {
		if (is_cut[i]) {
			ret_cnt++;
		}
	}
	cout << ret_cnt << '\n';
	for (int i = 1; i <= v; i++) {
		if (is_cut[i]) {
			cout << i << ' ';
		}
	}

	return 0;
}