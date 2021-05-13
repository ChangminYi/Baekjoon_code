//시간초과

#include <iostream>

using namespace std;

int gcd(int a, int b) {
	if (b == 0) { return a; }
	else { return gcd(b, a % b); }
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n = 0;
	while (true) {
		cin >> n;
		if (n == 0) {
			break;
		}
		else {
			int counter = 1;
			for (int i = 2; i < n; i++) {
				if (gcd(n, i) == 1) { counter++; }
			}
			cout << counter << '\n';
		}
	}

	return 0;
}