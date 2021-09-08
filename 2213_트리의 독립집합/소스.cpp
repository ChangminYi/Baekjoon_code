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
* �޸� ������ ���Ͽ� Ʈ���� ���� �������� �ʾҰ�,
* dfs�� ������ ���� ���� ���� ���� ��带 ���ڷ� ������.
* ���� ä�� �� �� 500kb ������ �޸𸮸� ������.
* �ӵ��� �� �� 8ms�� ������.
*/

int find_max(int cur, int prev, bool is_in_set) {
	int col_idx = (is_in_set ? 1 : 0);

	/*
	* �̹� ���� ������ �״�� ��ȯ, ������ Ž�� ����
	* ���� ���� ��尡 ���տ� ���ԵǾ��ٸ�, �ڽ� ������ �ݵ�� ���տ� ���ԵǸ� �ȵȴ�.
	* �׷��Ƿ� �ٷ� ���� ��� ���� ���տ� ���Ե��� ���� �ڽ� ����� dp������ ���Ѵ�.
	* ���� ���� ��尡 ���տ� ���Ե��� �ʾҴٸ�, �ڽ� ������ ���� ���θ� Ž���Ѵ�.
	* �׷��Ƿ� �ڽ� ��带 ���տ� ������ ���� �������� ���� ���� �� �� ���ؼ�,
	* �� ū ���� ���� ���� �ڽ��� dp���� ���Ѵ�.
	* �׸��� �ڽ� ��� �� ���տ� ���Խ����� ����� ���� �� ū �ڽ� ����
	* ���� ǥ�ø� �Ͽ� ���տ� �����Ѵ�.
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