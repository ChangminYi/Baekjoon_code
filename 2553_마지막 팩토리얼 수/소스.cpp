#include <iostream>

typedef unsigned long long ull;
using namespace std;

int main() {
	ull N = 0;
	cin >> N;

	ull temp = 1;
	for (ull i = 2; i <= N; i++) {
		temp *= i;
		while (temp % 10 == 0) {
			temp /= 10;
		}
		temp %= 1000000000;
	}

	cout << temp % 10;

	return 0;
}