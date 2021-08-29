#include <iostream>

using namespace std;

typedef long long lli;
typedef pair<lli, lli> plli;

int ccw(const plli& a, const plli& b, const plli &c) {
	lli tmp = a.first * b.second + b.first * c.second + c.first * a.second;
	tmp -= a.second * b.first + b.second * c.first + c.second * a.first;
	return (tmp == 0 ? 0 : (tmp > 0 ? 1 : -1));
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	plli a, b, c, d;
	cin >> a.first >> a.second >> b.first >> b.second;
	cin >> c.first >> c.second >> d.first >> d.second;

	int ccw_1 = ccw(a, b, c) * ccw(a, b, d);
	int ccw_2 = ccw(c, d, a) * ccw(c, d, b);

	if (ccw_1 <= 0 && ccw_2 <= 0) {
		if (ccw_1 == 0 && ccw_2 == 0) {
			if (a.first == c.first) {
				if (a.second > b.second) {
					swap(a, b);
				}
				if (c.second > d.second) {
					swap(c, d);
				}

				if (a.second <= d.second && c.second <= b.second) {
					cout << 1;
				}
				else {
					cout << 0;
				}
			}
			else {
				if (a.first > b.first) {
					swap(a, b);
				}
				if (c.first > d.first) {
					swap(c, d);
				}

				if (a.first <= d.first && c.first <= b.first) {
					cout << 1;
				}
				else {
					cout << 0;
				}
			}
		}
		else {
			cout << 1;
		}
	}
	else {
		cout << 0;
	}

	return 0;
}