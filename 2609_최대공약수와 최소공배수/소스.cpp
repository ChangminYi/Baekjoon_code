#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
	if (a % b == 0) {
		return b;
	}
	else {
		return gcd(b, a % b);
	}
}

int main() {
	int a = 0, b = 0;
	cin >> a >> b;

	int lo = gcd(a, b);

	cout << lo << '\n' << lo * (a / lo) * (b / lo);

	return 0;
}