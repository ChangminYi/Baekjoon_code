#include <iostream>
#include <vector>
#include <deque>
#include <numeric>
#include <algorithm>

using namespace std;

struct edge {
	int node1, node2;
	int weight;
	edge(int n1 = 0, int n2 = 0, int w = 0) :node1(n1), node2(n2), weight(w) {
	}
};

const int MAX_EDGE = 27;
const int MAX_NODE = 10;

int n, m;
edge all_edge[MAX_EDGE];
int parent[MAX_NODE + 1];
int degree[MAX_NODE + 1];
int max_degree[MAX_NODE + 1];
deque<int> stk;
deque<int> mst;
vector<bool> perm;

istream& operator>>(istream& in, edge& e) {
	in >> e.node1 >> e.node2 >> e.weight;
	if (e.node1 > e.node2) {
		swap(e.node1, e.node2);
	}
	return in;
}

int _find(int x) {
	return (parent[x] == x ? x : parent[x] = _find(parent[x]));
}

void _union(int x, int y) {
	int f_x = _find(x), f_y = _find(y);
	if (f_x > f_y) {
		swap(f_x, f_y);
	}
	parent[f_y] = f_x;
}

bool all_connected() {
	for (int i = 1; i < n; i++) {
		if (_find(i) != _find(i + 1)) {
			return false;
		}
	}
	return true;
}

bool right_degree() {
	for (int i = 1; i <= n; i++) {
		if (degree[i] > max_degree[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	if (m + 1 < n) {
		cout << "NO";
	}
	else {
		perm.resize(m, false);
		for (int i = 1; i <= n; i++) {
			cin >> max_degree[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> all_edge[i];
		}
		for (int i = 0; i < n - 1; i++) {
			perm[i] = true;
		}

		int min_cost = INT32_MAX;
		do {
			int tmp_cost = 0;

			stk.clear();
			iota(parent, parent + MAX_NODE + 1, 0);
			fill(degree, degree + MAX_NODE + 1, 0);

			for (int i = 0; i < m; i++) {
				if (perm[i]) {
					stk.push_back(i);
				}
			}

			for (int& idx : stk) {
				edge& cur = all_edge[idx];

				degree[cur.node1]++, degree[cur.node2]++;
				tmp_cost += cur.weight;
				_union(cur.node1, cur.node2);
			}

			if (all_connected() && right_degree() && tmp_cost < min_cost) {
				min_cost = tmp_cost;
				mst = deque<int>(stk);
			}
		} while (prev_permutation(perm.begin(), perm.end()));

		if (min_cost == INT32_MAX) {
			cout << "NO";
		}
		else {
			cout << "YES\n";
			for (int& idx : mst) {
				cout << all_edge[idx].node1 << ' ' << all_edge[idx].node2 << '\n';
			}
		}
	}

	return 0;
}