#include <iostream>
#include <iomanip>

using namespace std;

#define MAX 1000000000000
typedef unsigned long long ulli;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N = 0;
	ulli res = 1;

	cin >> N;

	for (ulli i = N; i >= 1; i--) {
		res *= i;
		while (res % 10 == 0) {
			res /= 10;
		}

		res %= MAX;
	}

	res %= 100000;
	cout.width(5);
	cout.fill('0');
	cout << res;

	return 0;
}