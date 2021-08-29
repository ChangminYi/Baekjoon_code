#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> dfs_val;
vector<bool> finish;
stack<int> stk;
vector<vector<int>> ans;
int cnt = 0;

int dfs(int cur) {
	dfs_val[cur] = ++cnt;
	stk.push(cur);

	int ret = dfs_val[cur];
	for (int& nxt : graph[cur]) {
		if (dfs_val[nxt] == 0) {
			ret = min(ret, dfs(nxt));
		}
		else if (!finish[nxt]) {
			ret = min(ret, dfs_val[nxt]);
		}
	}

	if (ret == dfs_val[cur]) {
		vector<int> scc;

		while (true) {
			int val = stk.top();
			stk.pop();
			scc.push_back(val);
			finish[val] = true;
			
			if (val == cur) {
				break;
			}
		}

		ans.push_back(scc);
	}

	return ret;
}

const bool vector_cmp(const vector<int>& a, const vector<int>& b) {
	return a.front() < b.front();
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int v, e;
	cin >> v >> e;
	graph = vector<vector<int>>(v + 1);
	dfs_val = vector<int>(v + 1, 0);
	finish = vector<bool>(v + 1, false);
	for (int i = 0, prnt, chld; i < e; i++) {
		cin >> prnt >> chld;
		graph[prnt].push_back(chld);
	}

	for (int i = 1; i <= v; i++) {
		if (dfs_val[i] == 0) {
			dfs(i);
		}
	}


	for (vector<int>& col : ans) {
		sort(col.begin(), col.end());
	}
	sort(ans.begin(), ans.end(), vector_cmp);

	cout << ans.size() << '\n';
	for (vector<int>& col : ans) {
		for (int& i : col) {
			cout << i << ' ';
		}
		cout << -1 << '\n';
	}

	return 0;
}