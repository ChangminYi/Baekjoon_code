#include <iostream>
#include <string>

using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b) {
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

	int N = 0, M = 0;
	unsigned long long A = 1, B = 1;
	int temp = 0;

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		A *= temp;
	}
	for (int i = 0; i < M; i++) {
		cin >> temp;
		B *= temp;
	}

	string res = to_string(gcd(A, B));
	if (res.size() > 9) {
		cout << res.substr(res.size() - 9);
	}
	else {
		cout << res;
	}

	return 0;
}