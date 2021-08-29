#include <iostream>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

typedef long long lli;
typedef pair<lli, lli> plli;
typedef pair<plli, plli> line;

int n;
vector<line> arg;
vector<int> parent;
map<int, int> group_size;

istream& operator>>(istream& in, line& p) {
	in >> p.first.first >> p.first.second >> p.second.first >> p.second.second;
	if (p.first > p.second) {
		swap(p.first, p.second);
	}
	return in;
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
	if (x > y) {
		swap(x, y);
	}
	parent[f_y] = f_x;
}

int ccw(plli a, plli b, plli c) {
	lli tmp = a.first * b.second + b.first * c.second + c.first * a.second;
	tmp -= a.second * b.first + b.second * c.first + c.second * a.first;
	return (tmp == 0 ? 0 : (tmp > 0 ? 1 : -1));
}

bool is_crossing(plli &a1, plli &a2, plli &b1, plli &b2) {
	if (ccw(a1, a2, b1) * ccw(a1, a2, b2) <= 0 &&
		ccw(b1, b2, a1) * ccw(b1, b2, a2) <= 0) {
		if ((a1.first > b1.first && a1.first > b2.first && a2.first > b1.first && a2.first > b2.first) ||
			(b1.first > a1.first && b1.first > a2.first && b2.first > a1.first && b2.first > a2.first)) {
			return false;
		}
		else if ((a1.second > b1.second && a1.second > b2.second && a2.second > b1.second && a2.second > b2.second) ||
			(b1.second > a1.second && b1.second > a2.second && b2.second > a1.second && b2.second > a2.second)) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	arg = vector<line>(n);
	parent = vector<int>(n);
	for (line& p : arg) {
		cin >> p;
	}
	iota(parent.begin(), parent.end(), 0);

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (is_crossing(arg[i].first, arg[i].second, arg[j].first, arg[j].second)) {
				_union(i, j);
			}
		}
	}

	int max_size = 0;
	for (int i = 0; i < n; i++) {
		if (_find(i) == i) {
			group_size.insert(make_pair(_find(i), 0));
		}
		
		group_size[_find(i)]++;
	}
	for (auto i = group_size.begin(); i != group_size.end(); i++) {
		max_size = max(max_size, i->second);
	}

	cout << group_size.size() << '\n' << max_size;

	return 0;
}