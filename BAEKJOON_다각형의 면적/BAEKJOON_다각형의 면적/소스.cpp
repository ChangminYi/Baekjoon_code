#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lli;
typedef pair<lli, lli> pint;

int n;
double res = 0;
vector<pint> coo;

lli ccw(const pint &a, const pint &b, const pint &c) {
	lli tmp = a.first * b.second + b.first * c.second + c.first * a.second;
	tmp -= a.second * b.first + b.second * c.first + c.second * a.first;
	return tmp;
}

double get_area(const pint& a, const pint& b, const pint& c) {
	return 0.5 * ccw(a, b, c);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	coo = vector<pint>(n);
	for (pint& p : coo) {
		cin >> p.first >> p.second;
	}
	
	for (int i = 1; i < n - 1; i++) {
		res += get_area(coo.front(), coo[i], coo[i + 1]);
	}

	cout.precision(1);
	cout << fixed << abs(res);

	return 0;
}