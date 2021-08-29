#include <iostream>
#include <cmath>
#include <numeric>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int g, l;
	cin >> g >> l;

	int max = l / g;
	for (int i = sqrt(max); i >= 1; i--) {
		if (max % i == 0) {
			int tmp_lo = g * i;
			int tmp_hi = g * (max / i);
			if (gcd(tmp_hi, tmp_lo) == g && lcm(tmp_hi, tmp_lo) == l) {
				cout << g * i << ' ' << g * (max / i);
				break;
			}
		}
	}

	return 0;
}