#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull getRes(ull a, ull b, ull c) {
	if (b == 0) {
		return 1;
	}
	else if (b == 1) {
		return a;
	}
	else {
		if (b % 2 == 1) {
			return ((getRes(a, b - 1, c) * a) % c);
		}
		else {
			ull temp = getRes(a, b / 2, c) % c;
			return ((temp * temp) % c);
		}
	}
}

int main() {
	int A = 0, B = 0, C = 0;
	cin >> A >> B >> C;

	cout << (getRes(A, B, C) % C);

	return 0;
}