#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;

int _find(int i) {
	if (parent[i] == i) {
		return i;
	}
	else {
		parent[i] = _find(parent[i]);
		return parent[i];
	}
}

void _union(int a, int b) {
	int par_a = _find(a);
	int par_b = _find(b);

	if (par_a < par_b) {
		parent[par_b] = par_a;
	}
	else {
		parent[par_a] = par_b;
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	parent = vector<int>(n);
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}

	int res = 0;
	for (int i = 1; i <= m; i++) {
		pair<int, int> p;
		cin >> p.first >> p.second;
		
		if (_find(p.first) == _find(p.second)) {
			res = i;
			break;
		}
		else {
			_union(p.first, p.second);
		}
	}

	cout << res;

	return 0;
}