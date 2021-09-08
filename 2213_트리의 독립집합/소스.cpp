#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

const int NOT_VISIT = -1;

int n;
vector<list<int>> graph;
vector<int> weight, trace;
vector<vector<int>> dp;
vector<bool> in_set;

/*
* 메모리 절약을 위하여 트리를 따로 구축하지 않았고,
* dfs를 실행할 때는 현재 노드와 이전 노드를 인자로 보냈음.
* 백준 채점 시 약 500kb 정도의 메모리를 절약함.
* 속도는 둘 다 8ms로 측정됨.
*/

int find_max(int cur, int prev, bool is_in_set) {
	int col_idx = (is_in_set ? 1 : 0);

	/*
	* 이미 값이 있으면 그대로 반환, 없으면 탐색 진행
	* 만약 현재 노드가 집합에 포함되었다면, 자식 노드들은 반드시 집합에 포함되면 안된다.
	* 그러므로 바로 현재 노드 값에 집합에 포함되지 않은 자식 노드의 dp값들을 더한다.
	* 만약 현재 노드가 집합에 포함되지 않았다면, 자식 노드들의 포함 여부를 탐색한다.
	* 그러므로 자식 노드를 집합에 포함한 값과 포함하지 않은 값을 둘 다 구해서,
	* 더 큰 값을 갖는 값을 자신의 dp값에 더한다.
	* 그리고 자식 노드 중 집합에 포함시켰을 경우의 값이 더 큰 자식 노드는
	* 따로 표시를 하여 집합에 포함한다.
	*/
	if (dp[cur][col_idx] == NOT_VISIT) {
		dp[cur][col_idx] = (is_in_set ? weight[cur] : 0);

		if (is_in_set) {
			for (const int& nxt : graph[cur]) {
				if (nxt != prev) {
					dp[cur][col_idx] += find_max(nxt, cur, false);
				}
			}
		}
		else {
			for (const int& nxt : graph[cur]) {
				if (nxt != prev) {
					int res1 = find_max(nxt, cur, false);
					int res2 = find_max(nxt, cur, true);

					in_set[nxt] = res1 < res2;
					dp[cur][col_idx] += max(res1, res2);
				}
			}
		}
	}

	return dp[cur][col_idx];
}

void get_trace(int cur, int prev, bool is_in_set) {
	if (is_in_set) {
		trace.push_back(cur);

		for (const int& nxt : graph[cur]) {
			if (nxt != prev) {
				get_trace(nxt, cur, false);
			}
		}
	}
	else {
		for (const int& nxt : graph[cur]) {
			if (nxt != prev) {
				get_trace(nxt, cur, in_set[nxt]);
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	graph.resize(n + 1);
	weight.resize(n + 1);
	in_set.resize(n + 1, false);
	dp.resize(n + 1, vector<int>(2, NOT_VISIT));

	for (int i = 1; i <= n; i++) {
		cin >> weight[i];
	}
	for (int i = 0, arg1, arg2; i < n - 1; i++) {
		cin >> arg1 >> arg2;
		graph[arg1].push_back(arg2);
		graph[arg2].push_back(arg1);
	}

	int res1 = find_max(1, 0, false);
	int res2 = find_max(1, 0, true);
	in_set[1] = res1 < res2;

	get_trace(1, 0, in_set[1]);
	sort(trace.begin(), trace.end());

	cout << max(res1, res2) << '\n';
	for (const int& i : trace) {
		cout << i << ' ';
	}

	return 0;
}