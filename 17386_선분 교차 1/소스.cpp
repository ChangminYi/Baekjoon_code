#include <iostream>

using namespace std;

typedef long long lli;
typedef pair<lli, lli> pint;

int ccw(pint& a, pint& b, pint& c) {
	lli tmp = a.first * b.second + b.first * c.second + c.first * a.second;
	tmp -= a.second * b.first + b.second * c.first + c.second * a.first;

	return (tmp == 0 ? 0 : (tmp > 0 ? 1 : -1));
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	pint a, b, c, d;
	cin >> a.first >> a.second;
	cin >> b.first >> b.second;
	cin >> c.first >> c.second;
	cin >> d.first >> d.second;

	if ((ccw(a, b, c) * ccw(a, b, d) < 0) && (ccw(c, d, a) * ccw(c, d, b) < 0)) {
		cout << 1;
	}
	else {
		cout << 0;
	}

	return 0;
}