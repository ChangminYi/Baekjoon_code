#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long lli;
typedef pair<lli, lli> plli;

int n;
vector<plli> dir;
deque<plli> stk;

istream& operator>> (istream& in, plli& p) {
	return in >> p.first >> p.second;
}

bool operator< (const plli& a, const plli& b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	return a.first < b.first;
}

double dist(const plli& a, const plli& b) {
	lli dist_x = b.first - a.first;
	lli dist_y = b.second - a.second;
	return sqrt(dist_x * dist_x + dist_y * dist_y);
}

int ccw(const plli& a, const plli& b, const plli& c) {
	lli tmp = a.first * b.second + b.first * c.second + c.first * a.second;
	tmp -= a.second * b.first + b.second * c.first + c.second * a.first;

	return (tmp == 0 ? 0 : (tmp > 0 ? 1 : -1));
}

bool cmp(const plli& a, const plli& b) {
	return (ccw(dir.front(), a, b) > 0)
		|| (ccw(dir.front(), a, b) == 0 && dist(dir.front(), a) < dist(dir.front(), b));
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	dir.resize(n);
	for (plli& p : dir) {
		cin >> p;
	}

	sort(dir.begin(), dir.end());
	sort(dir.begin() + 1, dir.end(), cmp);

	stk.push_back(dir[0]), stk.push_back(dir[1]);
	for (int i = 2; i < n; i++) {
		while (stk.size() >= 2 && ccw(*(stk.end() - 2), *(stk.end() - 1), dir[i]) <= 0) {
			stk.pop_back();
		}

		stk.push_back(dir[i]);
	}

	cout << stk.size();

	return 0;
}