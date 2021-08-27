#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;

int n;
vector<pint> dir;
set<pint> cand;

istream& operator>>(istream& in, pint& p) {
	return in >> p.first >> p.second;
}

int get_dist(const pint& a, const pint& b) {
	int x = a.first - b.first;
	int y = a.second - b.second;
	return x * x + y * y;
}

pint get_reverse_pair(const pint& p) {
	return make_pair(p.second, p.first);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	dir.resize(n);
	for (pint& p : dir) {
		cin >> p;
	}
	sort(dir.begin(), dir.end());
	dir.erase(unique(dir.begin(), dir.end()), dir.end());

	cand.insert(get_reverse_pair(dir[0]));
	cand.insert(get_reverse_pair(dir[1]));
	int min_dist = get_dist(dir[0], dir[1]);
	int idx = 0;
	for (int i = 2; i < n; i++) {
		while (idx < i) {
			pint tmp_dir = get_reverse_pair(dir[idx]);
			int tmp_dist = dir[i].first - dir[idx].first;

			if (tmp_dist * tmp_dist <= min_dist) {
				break;
			}
			else {
				cand.erase(tmp_dir);
				idx++;
			}
		}

		pint lo_dir = make_pair(dir[i].second - (int)sqrt(min_dist), INT32_MIN);
		pint hi_dir = make_pair(dir[i].second + (int)sqrt(min_dist), INT32_MAX);
		for (auto j = cand.lower_bound(lo_dir); j != cand.upper_bound(hi_dir); j++) {
			pint cmp_dir = get_reverse_pair(*j);
			min_dist = min(min_dist, get_dist(dir[i], cmp_dir));
		}

		cand.insert(get_reverse_pair(dir[i]));
	}

	cout << min_dist;

	return 0;
}