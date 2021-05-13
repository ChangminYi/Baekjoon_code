#include <iostream>
#include <algorithm>

using namespace std;

bool off[10] = { false };

int lengthDecimal(int i) {
	if (0 <= i && i < 10) { return 1; }
	else if (10 <= i && i < 100) { return 2; }
	else if (100 <= i && i < 1000) { return 3; }
	else if (1000 <= i && i < 10000) { return 4; }
	else if (10000 <= i && i < 100000) { return 5; }
	else if (100000 <= i && i < 1000000) { return 6; }
	else if (1000000 <= i && i < 10000000) { return 7; }
	return -1;
}

bool canMake(int i) {
	do {
		if (off[i % 10]) {
			return false;
		}
		i /= 10;
	} while (i > 0);
	return true;
}

int getNumber(int toGo) {
	for (int i = 0, lo, hi; ; i++) {
		lo = toGo - i, hi = toGo + i;

		if (canMake(lo) && lo >= 0) {
			return lengthDecimal(lo) + i;
		}
		if (canMake(hi)) {
			return lengthDecimal(hi) + i;
		}
	}
	return -1;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N = 0, leng = 0;
	cin >> N >> leng;
	for (int i = 0, temp; i < leng; i++) {
		cin >> temp;
		off[temp] = true;
	}
	
	if (leng == 10) {
		cout << abs(N - 100);
	}
	else {
		cout << min(abs(N - 100), getNumber(N));
	}

	return 0;
}