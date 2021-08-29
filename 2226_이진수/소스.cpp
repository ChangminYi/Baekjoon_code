#include <iostream>
#include <vector>

using namespace std;
typedef long long lint;

int main() {
	lint N = 0;
	cin >> N;

	lint ans_0 = 0, ans_1 = 1;
	for (lint i = 0, temp_0 = 0, temp_1 = 0; i < N - 1; i++) {
		temp_0 = ans_0 + ans_1;
		temp_1 = temp_0;
		if (i % 2 == 1) { temp_0--; }
		ans_0 = temp_0;
		ans_1 = temp_1;
	}


	cout << ans_0;

	return 0;
}