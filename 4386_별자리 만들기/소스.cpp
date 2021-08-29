#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef pair<double, double> pdouble;
typedef pair<int, int> pint;

vector<int> parent;
vector<pdouble> argd;
vector<pair<double, pint>> dist;

double get_distance(pdouble& a, pdouble& b) {
	return sqrt(pow(abs(a.first - b.first), 2) + pow(abs(a.second - b.second), 2));
}

int _find(int x) {
	if (parent[x] == x) {
		return x;
	}
	else {
		parent[x] = _find(parent[x]);
		return parent[x];
	}
}

void _union(int x, int y) {
	int p_x = _find(x);
	int p_y = _find(y);

	if (p_x < p_y) {
		parent[p_y] = p_x;
	}
	else {
		parent[p_x] = p_y;
	}
}

bool in_same_set(int x, int y) {
	if (_find(x) == _find(y)) {
		return true;
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;
	argd = vector<pdouble>(n);
	parent = vector<int>(n);
	for (int i = 0; i < n; i++) {
		cin >> argd[i].first >> argd[i].second;
		parent[i] = i;
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			dist.push_back(make_pair(get_distance(argd[i], argd[j]), make_pair(i, j)));
		}
	}
	sort(dist.begin(), dist.end());

	double res = 0;
	for (pair<double, pint>& d : dist) {
		int frt = d.second.first;
		int bck = d.second.second;

		if (!in_same_set(frt, bck)) {
			_union(frt, bck);
			res += d.first;
		}
	}

	cout << fixed;
	cout.precision(2);
	cout << res;

	return 0;
}