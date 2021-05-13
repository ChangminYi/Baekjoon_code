#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

uint32_t isPrime(uint32_t num) {
	if (num == 1) { return 0; }
	else if (num == 2) { return 1; }
	else {
		for (uint32_t i = 2; i <= sqrt(num); i++) {
			if (num % i == 0) {
				return 0;
			}
		}
		return 1;
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	uint32_t N = 0;
	cin >> N;
	vector<uint32_t> argi = vector<uint32_t>(N);
	for (uint32_t &i : argi) {
		cin >> i;
	}

	int count = 0;
	for (uint32_t i = 0; i < argi.size(); i++) {
		count += isPrime(argi[i]);
	}
	cout << count;

	return 0;
}