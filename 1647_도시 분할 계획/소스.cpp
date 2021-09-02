#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

typedef long long lli;
struct edge {
	int weight = 0;
	int node1 = 0, node2 = 0;
	edge(int n1, int n2, int w) :node1(n1), node2(n2), weight(w) {}
};

int n, m;
vector<int> parent;
priority_queue<edge, vector<edge>, greater<edge>> pq;

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

bool operator>(const edge& lhs, const edge& rhs) {
	return lhs.weight > rhs.weight;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	parent.resize(n + 1);
	iota(parent.begin(), parent.end(), 0);

	for (int i = 0, n1, n2, w; i < m; i++) {
		cin >> n1 >> n2 >> w;
		pq.push(edge(n1, n2, w));
	}

	lli total_mst_weight = 0;
	int edge_cnt = 0, max_weight = 0;
	while (!pq.empty()) {
		edge cur = pq.top();
		pq.pop();

		if (_find(cur.node1) != _find(cur.node2)) {
			_union(cur.node1, cur.node2);
			total_mst_weight += cur.weight;
			max_weight = max(max_weight, cur.weight);
			if (++edge_cnt == n - 1) {
				break;
			}
		}
	}

	cout << total_mst_weight - max_weight;

	return 0;
}