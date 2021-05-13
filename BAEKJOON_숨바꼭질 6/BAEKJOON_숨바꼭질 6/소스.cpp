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
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, S = 0;
	cin >> N >> S;

	vector<int> dist(N);
	for (int &i : dist) {
		cin >> i;
		i = abs(S - i);
	}

	int minVal = dist.front();
	for (uint32_t i = 1; i < dist.size(); i++) {
		minVal = gcd(minVal, dist[i]);
	}

	cout << minVal;

	return 0;
}