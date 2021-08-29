#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;
typedef pair<double, pint> edge;

int n, m;
vector<int> parent;
vector<edge> all_edge;
vector<pint> dir;

double get_dist(const pint& a, const pint& b) {
	long long dist_x = a.first - b.first;
	long long dist_y = a.second - b.second;
	return sqrt(dist_x * dist_x + dist_y * dist_y);
}

int _find(int x) {
	if (parent[x] == x) {
		return x;
	}
	else {
		return parent[x] = _find(parent[x]);
	}
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

	cin >> n >> m;
	parent = vector<int>(n + 1);
	iota(parent.begin(), parent.end(), 0);
	dir = vector<pint>(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> dir[i].first >> dir[i].second;
	}
	for (int i = 0, node1, node2; i < m; i++) {
		cin >> node1 >> node2;
		_union(node1, node2);
	}

	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			double tmp_dist = get_dist(dir[i], dir[j]);
			all_edge.push_back(make_pair(tmp_dist, make_pair(i, j)));
		}
	}

	int connect_count = m;
	double dist_sum = 0;
	sort(all_edge.begin(), all_edge.end());
	for (edge& e : all_edge) {
		if (_find(e.second.first) != _find(e.second.second)) {
			connect_count++;
			dist_sum += e.first;
			_union(e.second.first, e.second.second);
		}

		if (connect_count == n - 1) {
			break;
		}
	}

	cout << fixed;
	cout.precision(2);
	cout << dist_sum;

	return 0;
}