#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
#include <functional>
#include <cctype>

using namespace std;

class edge {
public:
	int node1 = 0;
	int node2 = 0;
	int weight = 0;
	edge(int _n1, int _n2, int _w) : node1(_n1), node2(_n2), weight(_w) {}
};

int n;
int total_weight = 0;
vector<int> parent;
priority_queue<edge, vector<edge>, greater<edge>> pq;

bool operator>(const edge& e1, const edge& e2) {
	return e1.weight > e2.weight;
}

int get_weight(const char c) {
	return (islower(c) ? c - 'a' + 1 : c - 'A' + 27);
}

int _find(int x) {
	if (parent[x] == x) {
		return x;
	}
	return parent[x] = _find(parent[x]);
}

void _union(int x, int y) {
	int f_x = _find(x), f_y = _find(y);
	if (f_x > f_y) {
		swap(f_x, f_y);
	}
	parent[f_y] = f_x;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	parent = vector<int>(n);
	iota(parent.begin(), parent.end(), 0);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			char tmp;
			cin >> tmp;

			if (tmp != '0') {
				int tmp_weight = get_weight(tmp);
				total_weight += tmp_weight;
				pq.push(edge(i, j, tmp_weight));
			}
		}
	}

	int connected_weight = 0;
	int edge_connected = 0;
	while (!pq.empty()) {
		edge cur = pq.top();
		pq.pop();

		int f_1 = _find(cur.node1);
		int f_2 = _find(cur.node2);
		if (f_1 != f_2) {
			connected_weight += cur.weight;
			edge_connected++;
			_union(f_1, f_2);
		}

		if (edge_connected == n - 1) {
			break;
		}
	}

	if (edge_connected < n - 1) {
		cout << -1;
	}
	else {
		cout << total_weight - connected_weight;
	}

	return 0;
}