#include <iostream>
#include <vector>
#include <cfloat>
#include <cmath>

using namespace std;

typedef pair<double, double> pdbl;

int testcase, n;
vector<pdbl> vec;
vector<bool> visit;

istream& operator>> (istream& in, pdbl& p) {
	return in >> p.first >> p.second;
}

void operator+= (pdbl& a, const pdbl b) {
	a.first += b.first;
	a.second += b.second;
}

double get_val() {
	pdbl p1 = make_pair(0, 0), p2 = make_pair(0, 0);
	for (int i = 0; i < n; i++) {
		visit[i] ? p1 += vec[i] : p2 += vec[i];
	}

	double dist_x = p1.first - p2.first;
	double dist_y = p1.second - p2.second;

	return sqrt(dist_x * dist_x + dist_y * dist_y);
}

double dfs(int cur, int depth) {
	if (depth == n / 2) {
		return get_val();
	}
	else {
		double min_val = DBL_MAX;
		for (int i = cur; i < n; i++) {
			visit[i] = true;
			min_val = min(min_val, dfs(i + 1, depth + 1));
			visit[i] = false;
		}

		return min_val;
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
	(cout << fixed).precision(6);

	cin >> testcase;
	do {
		cin >> n;
		vec = vector<pdbl>(n);
		visit = vector<bool>(n, false);
		for (pdbl& p : vec) {
			cin >> p;
		}

		cout << dfs(0, 0) << '\n';
	} while (--testcase > 0);

	return 0;
}